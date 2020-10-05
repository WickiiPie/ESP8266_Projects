int led1 = D0;
int led2 = D1;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  Serial.println();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(led1,HIGH);
 digitalWrite(led2,LOW);
 delay(500);
 digitalWrite(led1,LOW);
 digitalWrite(led2,HIGH);
 delay(500);
}
