#include <esp_now.h>
#include <WiFi.h>

#define LED_BUILTIN 4

unsigned long previousMillis = 0;  // will store last time LED was updated

const long interval = 1000;  // interval at which to blink (milliseconds)
uint8_t broadcastAddress[] = { 0x98, 0xCD, 0xAC, 0x31, 0x59, 0xBC };

typedef struct struct_message {
  char info[32];
  float _temp;
  int _ledState;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Data Status:  ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("ESP FAILED TO INITATE");
    ESP.restart();
    return;
  }
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to connect to Peer");
    ESP.restart();
  }
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  unsigned long currentMillis = millis();
  int ledState = 0;

  Serial.print("currentMillis : ");
  Serial.println(currentMillis);

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = 0;
      Serial.println("FLASH ON");
      Serial.println(myData._ledState);

    } else {
      ledState = 1;
      Serial.println("FLASH OFF");
    }

    digitalWrite(LED_BUILTIN, ledState);
  }

  strcpy(myData.info, "esp32");
  myData._ledState = ledState;
  myData._temp = 18.84;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("SENT WITH SUCCESS");
delay(1000);
  } else {
    Serial.println("SEND FAILED");
    delay(2000);
  }
}
