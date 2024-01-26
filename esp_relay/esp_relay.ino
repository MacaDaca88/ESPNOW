#include "ota.h"

#define RELAY 33
#define LED 4
#define BUTTON 19

bool _button = true;
bool _relay = false;
bool _led = false;
unsigned long oldTime;
#define serialTime 1000

void setup() {
  Serial.begin(115200);
    WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  otaInit();
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(LED, 0);
  digitalWrite(RELAY, 0);
}

void loop() {
  ArduinoOTA.handle();

  _button = digitalRead(BUTTON);
  if (millis() - oldTime > serialTime) {
    oldTime = millis();
    Serial.print("_relay");
    Serial.println(_relay);

    Serial.print("_led");
    Serial.println(_led);

    Serial.print("_button");
    Serial.println(_button);
  }
  if (_button == false) {
    _relay = true;
    _led = true;
    digitalWrite(RELAY, 1);
    digitalWrite(LED, 1);

  } else {
    _relay = false;
    _led = false;

    digitalWrite(RELAY, 0);
    digitalWrite(LED, 0);
  }
}
