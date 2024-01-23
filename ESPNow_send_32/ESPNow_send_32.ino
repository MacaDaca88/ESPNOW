#include <esp_now.h>
#include <WiFi.h>

#define LED_BUILTIN 4  //GPIO4 Flash

unsigned long previousMillis = 0;  // will store last time LED was updated

const long interval = 1000;                                           // interval at which to blink
uint8_t broadcastAddress[] = { 0x98, 0xCD, 0xAC, 0x31, 0x59, 0xBC };  // Mac address for reciver board

typedef struct struct_message {  // struct to hold variables to send
  char info[32];
  float _temp;
  bool _ledState;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;  // variable to hold mac/channel info to connect


// Serial print after each packet sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Data Status:  ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);       // start serial @115200
  WiFi.mode(WIFI_STA);        // set wifi to station mode
  if (esp_now_init() != 0) {  // if esp_now fails to initaite
    Serial.println("ESP FAILED TO INITATE");
    ESP.restart();  // restart esp
    return;         // exit
  }
  esp_now_register_send_cb(OnDataSent);  //

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
  bool _ledState = false;


  Serial.print("currentMillis : ");
  Serial.println(currentMillis);


  // if elapsed time is greater the interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // reset timer to 0

    if (ledState == LOW) {  // switch led on
      ledState = 0;
      Serial.println("FLASH ON");
      Serial.println(myData._ledState);

    } else {
      // switch led off
      ledState = 1;
      Serial.println("FLASH OFF");
    }

    digitalWrite(LED_BUILTIN, ledState);  // toggle led on/off
    _ledState = ledState;
  }
  // data to be sent
  strcpy(myData.info, "esp32");         // display board name
  myData._ledState = _ledState;      // ledstate
  myData._temp = random(1.00, 100.00);  // temps

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("SENT WITH SUCCESS");
    delay(1000);
  } else {
    Serial.println("SEND FAILED");
    delay(2000);
  }
}
