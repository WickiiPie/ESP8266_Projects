int trigPin = D7;
int echoPin = D8;
void setup(){
Serial.begin(115200);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
void loop(){
long duration, dist;
digitalWrite(trigPin,LOW);
delayMicroseconds(2);
digitalWrite(trigPin,HIGH);
delayMicroseconds(5);
digitalWrite(trigPin,LOW);
duration = pulseIn(echoPin, HIGH);
dist = (duration/29)/2;
Serial.print("Distance = ");
Serial.print(dist);
Serial.println(" cm");
delay(1000);
}
