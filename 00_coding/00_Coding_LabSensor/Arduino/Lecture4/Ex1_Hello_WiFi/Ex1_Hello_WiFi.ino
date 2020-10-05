#include <ESP8266WiFi.h> //esp8266 lib

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin("-XIV-X", "wp127001"); //wifi ssid and pass
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { //check connection
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());//print node ipaddress
}

void loop() {
  
  }

