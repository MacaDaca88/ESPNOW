#include <ESP8266WiFi.h>
#include <espnow.h>
#define LED 13
typedef struct struct_message {
  char info[32];
  float _temp;
  bool _ledState;
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t* mac, uint8_t* incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));  // recall the incoming data to print
  Serial.print("bytes recived : ");
  Serial.println(len);
  Serial.print("Board : ");
  Serial.println(myData.info);
  Serial.print("Temps : ");
  Serial.println(myData._temp);
  Serial.print("Led State : ");
  Serial.println(myData._ledState);
  Serial.write(myData._ledState ? "on\n" : "off\n");  // print when lights on or off
  Serial.println("      ");                           // creates a gap between transmissions
  Serial.println("      ");
  digitalWrite(LED_BUILTIN, myData._ledState ? 1 : 0);  //set GPI02 ledState 1= on :  0= off
}



void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);           // set wifi in station mode
  pinMode(LED_BUILTIN, OUTPUT);  // set pinMode for LED_BUILTIN OUTPUT
  if (esp_now_init() != 0) {
    Serial.println("ERROR");
    ESP.restart();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
