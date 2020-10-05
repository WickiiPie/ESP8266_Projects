#include <ESP8266WiFi.h>
 
const char* ssid = "Engineering1"; //Change to your Access Point
const char* password = "engineering1"; //Change to your AP PW
const char* host = "192.168.1.44"; //Change to your server IP address

 
WiFiClient client;
int switchPin=D0;

void setup() { 
  pinMode(switchPin,INPUT);
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() { 
 

 if (client.connect(host, 80)) {
  Serial.println("\n------------ Connect to the server ------------");
  Serial.print("      * Send to Server: ");

  int x = digitalRead(switchPin);

  client.print(x);
  
   
  Serial.println(x); 
  
  } else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  client.stop();  
  Serial.println("------------ Disconnect, Wait 15 Seconds ----------");
  delay(150); //every 15 seconds
  
}
