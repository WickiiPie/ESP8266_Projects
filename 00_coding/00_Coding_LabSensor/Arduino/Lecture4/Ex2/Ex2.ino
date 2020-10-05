#include <ESP8266WiFi.h> //esp8266 lib
int led1 = D0;
int led2 = D1;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin("MSI_XIV", "wp127001"); //wifi ssid and pass
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { //check connection
    delay(500);
    digitalWrite(led2,HIGH);
    digitalWrite(led1,LOW);
    Serial.print(".");
  }
  Serial.println();
  digitalWrite(led2,LOW);
  digitalWrite(led1,HIGH);
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());//print node ipaddress
} 

void loop() {
  
}

  
