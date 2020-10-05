#include <ESP8266WiFi.h>
 
const char* ssid = "MyAccessPoint"; //Change to your Access Point
const char* password = "12345678"; //Change to your AP PW
const char* host = "192.168.4.1"; //Change to your server IP address
int Count=0;
 
WiFiClient client;
 
void setup() { 
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
    Serial.println("\n--------- Connect to the server -----------");
    Serial.print("   * Send to Server: ");
    Serial.println("Humi");  
    // This will send the data to the server
    client.print("Humi");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.print("   * Receive from Server: ");
        Serial.println(data);
        Count = data.toInt()+1;
      }
    }
    client.stop();    
    delay(3000);     
  } else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  Serial.println("---------Disconnect, Wait 15 Seconds ----------");
  delay(100); //every 15 seconds
}

