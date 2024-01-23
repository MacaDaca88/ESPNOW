

String incomingString;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  delay(2000);
  digitalWrite(LED_BUILTIN, 0);
  delay(1000);

}

void loop() {

  if (Serial.available() > 0) {
    incomingString = Serial.readString();
    if (incomingString.equals("on")) {
      Serial.println("on");
      digitalWrite(LED_BUILTIN, 1);
    } else {
      Serial.println("off");
      digitalWrite(LED_BUILTIN, 0);
    }
  }
}