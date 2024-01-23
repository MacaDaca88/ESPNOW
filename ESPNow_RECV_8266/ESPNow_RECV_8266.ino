#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
  char info[32];
  float _temp;
  bool _ledState;
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t* mac, uint8_t* incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("bytes recived : ");
  Serial.println(len);
  Serial.print("Board : ");
  Serial.println(myData.info);
  Serial.print("Temps : ");
  Serial.println(myData._temp);
  Serial.print("Led State : ");
  Serial.println(myData._ledState);
  Serial.println("      ");
  Serial.println("      ");
}



void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("ERROR");
    ESP.restart();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.write(myData._ledState ? "on" : "off");
  digitalWrite(LED_BUILTIN ,myData._ledState );
}
