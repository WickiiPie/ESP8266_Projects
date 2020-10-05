#include <ESP8266WiFi.h>              
const char* ssid = "3bb-Wichphon"; //Access Point SSID              
const char* password = "0818647157"; //Access Point Password       
WiFiServer server(80);              
 
void setup() {
  Serial.begin(115200);       
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);           
  while (WiFi.status() != WL_CONNECTED)    
  {
        delay(500);
        Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");       
  server.begin();                   
  Serial.println("Server started");
  Serial.println(WiFi.localIP());           
}
 
void loop() {
  WiFiClient client = server.available();   
  if (!client) {            
    return;
  }   
  Serial.println("new client");
  Serial.print(analogRead(A0));
  while(!client.available())
  {
    delay(1);
  }  
  
//Create a HTTP response as the String variable named "web"
//Header of this HTTP response
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//Body of this HTTP response
  web += "Resistance = ";
  web += String(analogRead(A0));
  client.print(web);
}



