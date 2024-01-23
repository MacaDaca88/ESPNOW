#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = { 0x98, 0xCD, 0xAC, 0x31, 0x59, 0xBC };

typedef struct struct_message {
  char info[32];
  float _temp;
  int _ledState;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Data Status:  ");
  if (sendStatus == 0) {
    Serial.println("Data Send Success");
  } else {
    Serial.println("FAILED");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("ESP FAIL");
    ESP.restart();
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {

  strcpy(myData.info, "ESP_8266 Mega");
  myData._ledState = random(0,1);
  myData._temp = 3.4;
  esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
}
