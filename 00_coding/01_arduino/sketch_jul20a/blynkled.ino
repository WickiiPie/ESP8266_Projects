#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//
//#define BLYNK_PRINT Serial

char authen[] = "sNu3unQKqDwmN4E1HWS69KeFZyAB9gti";
char ssid[] = "-XIV-X";
char pass[] = "wp127001";
unsigned char count = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println();
  Blynk.begin(authen, ssid, pass);
  
  pinMode(2, OUTPUT);
}
BLYNK_WRITE(10) {  // vPin is the Virtual Pin assigned to a Button Widget
 unsigned char state = 0;
 state = param.asInt();
 digitalWrite(2,state);
 Blynk.virtualWrite(V5, state); //sending to Blynk V5
 if(count >10 )
 {
  count = 0;
 }
 else
 {
  count++;
  
 }
 Blynk.virtualWrite(V6, count); //sending to Blynk V6
}
void loop() {
  // put your main code here, to run repeatedly:

  Blynk.run();
  
}
