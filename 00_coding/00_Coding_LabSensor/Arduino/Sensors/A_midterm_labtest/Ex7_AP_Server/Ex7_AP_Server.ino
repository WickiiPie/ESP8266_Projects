#include <ESP8266WiFi.h>
int LDR = A0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("MyAccessPoint", "12345678");
  if (result == true) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
  }
  //IPAddress apip = WiFi.softAPIP();

  server.begin(); //Start working as a server
  Serial.println("Server starts.");
  Serial.print("Server IP Address: ");
  Serial.println(WiFi.softAPIP());
  pinMode(LDR, INPUT);

}

void loop() {
  int ldr = digitalRead(LDR);
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n------------- [Client connected] ------------");
    while (client.connected()) {
      if (client.available()) {
        Serial.print("     * Send to Client: ");
        Serial.println(ldr);
        client.print(ldr);
        client.print('\r');
      }
    }
    delay(10);
    client.stop();
    Serial.println("------------- Disconnect, Wait 15 Seonds ---------------");
  }
}

