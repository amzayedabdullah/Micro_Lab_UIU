String input = ""; // to store user input

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Type 'on' or 'off' to control LED:");
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n'); // read until newline
    input.trim(); // remove whitespace

    if (input == "on") {
      digitalWrite(13, HIGH);
      Serial.println("LED turned ON");
    }
    else if (input == "off") {
      digitalWrite(13, LOW);
      Serial.println("LED turned OFF");
    }
    else {
      Serial.println("Invalid input. Type 'on' or 'off'.");
    }
  }
}
