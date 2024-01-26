#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4);  //rx, tx

uint8_t broadcastAddress[] = { 0x98, 0xCD, 0xAC, 0x31, 0x59, 0xBC };  // Mac address for reciver board
bool trigger1 = false;


typedef struct struct_message {
  char info[32];
  bool _trigger1;

} struct_message;

struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 500;  // send readings timer

char rx;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  } else {
    Serial.println("Delivery fail");
  }
}


void setup() {
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  mySerial.begin(115200);
  // Init Serial Monitor
  Serial.begin(115200);
  delay(50);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    // Init ESP-NOW
    Serial.println("Error initializing ESP-NOW");
    ESP.restart();
  }
  return;
  Serial.println(" ESP-NOW connected");

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  while (Serial.available()) {
    rx = Serial.read();
    Serial.print(rx);


    if ((millis() - lastTime) > timerDelay) {
      // Set values to send
      strcpy(myData.info, "Trigger1");
      myData._trigger1 = (1, 0);
      mySerial.write(1);
      // Send message via ESP-NOW
      esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

      lastTime = millis();
    }
  }
}
