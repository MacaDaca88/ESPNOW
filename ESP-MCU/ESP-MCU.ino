String incomingString;
typedef struct struct_message {
  bool _ledState;
} struct_message;

struct_message myData;

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
      myData._ledState = true;
    } else {
      myData._ledState = false;
    }

    if (myData._ledState) {
      Serial.println("Received LED State: ON");
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on
    } else {
      Serial.println("Received LED State: OFF");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
    }
  }
}