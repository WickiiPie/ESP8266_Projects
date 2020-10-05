#include <ESP8266WiFi.h>
 
const char* ssid = "3bb-Wichphon"; //Change to your Access Point
const char* password = "0818647157"; //Change to your AP PW
const char* host = "192.168.137.30"; //Change to your server IP address
int Count=0;
WiFiClient client;
 
void setup() {
  pinMode(D0, OUTPUT);
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
}
 
void loop() { 
  if (client.connect(host, 80)) {
    client.print("req"); 
    
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.println(data);
        if (data=="0")digitalWrite(D0,0);
        if (data=="1")digitalWrite(D0,1);
      }
    }
    client.stop();        
  } else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  Serial.println("---------Disconnect, Wait 15 Seconds ----------");
  //delay(100); //every 15 seconds
}

