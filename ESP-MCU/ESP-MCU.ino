

String incomingString;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  Serial.println("on");
  delay(2000);

  digitalWrite(LED_BUILTIN, 0);
  Serial.println("off");
  delay(1000);
}

void loop() {

  while (Serial.available()) {
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