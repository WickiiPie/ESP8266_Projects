#include <ESP8266WiFi.h>

const char* ssid = "Babe"; //Change to your Access Point
const char* password = "18032540"; //Change to your Access Point PW

WiFiServer server(80);
boolean state = false;
void setup() {
  pinMode(D0,OUTPUT);
  digitalWrite(D0,LOW);
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
  server.begin(); //Start working as a server
  Serial.println("Server starts.");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n------------- [Client connected] ------------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.println(data);    
        if(data == "1"){
          state=!state;
          digitalWrite(D0,state);
        }
      }
    }
    //delay(150);
    client.stop();
  }
}

