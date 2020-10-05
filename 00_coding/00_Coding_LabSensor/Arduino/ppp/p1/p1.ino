int a = D0;
int b = D1;
void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  delay(3000);
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  delay(3000);
}
