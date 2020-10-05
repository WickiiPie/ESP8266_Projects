#include <ESP8266WiFi.h>
#define LED D1                  
const char* ssid = "Bozz"; //Access Point SSID              
const char* password = "88888888";  //Access Point Password
unsigned char status_led=0;         
WiFiServer server(80);              
 
void setup() {
  Serial.begin(115200);             
  pinMode(LED, OUTPUT);         
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
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');         
  Serial.println(req);              
  client.flush();
  if (req.indexOf("/ledoff") != -1)         
  {
    status_led=0;                   
    digitalWrite(LED,LOW);          
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)      
  {
    status_led=1;                   
    digitalWrite(LED,HIGH);         
    Serial.println("LED ON");
  }
}

