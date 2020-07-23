void setup() {
  pinMode(D4, OUTPUT);     // Initialize GPIO2 pin as an output

}

void loop() {
  digitalWrite(D4, LOW);   // Turn the LED on by making the voltage LOW
  digitalWrite(16, HIGH);
  delay(1000);            // Wait for a second
  digitalWrite(D4, HIGH);  // Turn the LED off by making the voltage HIGH
  digitalWrite(16, LOW);
  delay(2000);            // Wait for two seconds
}
