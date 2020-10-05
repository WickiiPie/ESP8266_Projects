#include <ESP8266WiFi.h>
int sw =D2;
int push;
WiFiClient client;
void setup() {
  pinMode(sw,INPUT);
  Serial.begin(115200);
  Serial.println();
  
}


void loop() {
      push =digitalRead(sw);
      Serial.println(push);
      delay(200);
      
    
    
}
