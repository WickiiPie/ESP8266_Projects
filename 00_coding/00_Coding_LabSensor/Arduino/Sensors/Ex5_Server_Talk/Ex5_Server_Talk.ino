#include <ESP8266WiFi.h>

const char* ssid = "WiFiatMFU"; //Change to your Access Point
const char* password = "Moon15Star18"; //Change to your Access Point PW

WiFiServer server(80);

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
  server.begin(); //Start working as a server
  Serial.println("Server starts.");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n--------- [Client connected]----------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        Serial.print("   * Receive from Client: ");
        Serial.println(data);
        Serial.print("   * Send to Client: ");
        Serial.println(data.toInt()+1);   
        client.print(data.toInt()+1);
        client.stop();
        Serial.println("--------- Disconnect, Wait 15 Seconds ----------");              
      }
    }
  }
}

