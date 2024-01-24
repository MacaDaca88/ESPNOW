char rx;



void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
}

void loop() {

  if (Serial.available()) {
    rx = Serial.read();
    Serial.print(rx);
  }
}
