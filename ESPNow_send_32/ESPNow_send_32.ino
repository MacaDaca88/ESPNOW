#include <esp_now.h>
#include <WiFi.h>

#define LED_BUILTIN 4  //GPIO4 Flash

unsigned long previousMillis = 0;  // will store last time LED was updated

const long interval = 500;                                           // interval at which to blink
uint8_t broadcastAddress[] = { 0x98, 0xCD, 0xAC, 0x31, 0x59, 0xBC };  // Mac address for reciver board

bool ledState = 0;

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


  // if elapsed time is greater the interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;                   // reset timer to 0
    digitalWrite(LED_BUILTIN, ledState = !ledState);  // toggle led on/off
    Serial.println(ledState ? "Led is ON" : "Led is OFF");
    Serial.println("currentMillis : " + String(currentMillis));

    // data to be sent
    strcpy(myData.info, "esp32");         // display board name
    myData._ledState = ledState;          // ledstate
    myData._temp = random(1.00, 100.00);  // temps

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.println("SENT WITH SUCCESS");
    } else {
      Serial.println("SEND FAILED");
    }
  }
}