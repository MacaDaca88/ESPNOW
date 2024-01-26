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
    Serial.println(incomingString);
    if (incomingString.equals("on\n")) {
      myData._ledState = true;
    } else if (incomingString.equals("off\n")) {
      myData._ledState = false;
    }

    if (myData._ledState == true) {
      Serial.println("Received LED State: ON");
      digitalWrite(LED_BUILTIN, myData._ledState ? 1 : 0);  // Turn the LED on
    } else {
      Serial.println("Received LED State: OFF");
    }
  }
}