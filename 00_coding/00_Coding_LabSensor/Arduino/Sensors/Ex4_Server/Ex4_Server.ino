#include <ESP8266WiFi.h>

const char* ssid = "Bozz"; //Change to your Access Point
const char* password = "88888888"; //Change to your Access Point PW
int led = D0;
bool state;
WiFiServer server(80);

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
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
        if (data == "0") {
          state=!state;
          digitalWrite(led, state);
          Serial.print("   * Receive from Client: ");
          Serial.println(data);
        } 
      }
    }
    delay(10);
    client.stop();
    Serial.println("--------------- Disconnect, Wait 15 Seonds ---------------");
  }
}

