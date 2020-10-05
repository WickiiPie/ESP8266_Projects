int sw = D3;
bool toggle;
int push;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(sw, INPUT);
  //digitalWrite(sw, HIGH);


}

void loop() {
  // put your main code here, to run repeatedly:
  //if(toggle==LOW)toggle!=toggle;
  push = digitalRead(sw);
  if (push == HIGH) {
    toggle = !toggle;
  }
  Serial.println(push);
  delay(500);

}
