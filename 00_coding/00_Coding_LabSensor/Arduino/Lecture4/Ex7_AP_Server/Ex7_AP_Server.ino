#include <ESP8266WiFi.h>
int LED1red = D0;
int LED2green = D1;
bool state1,state2;
WiFiServer server(80);

void setup() {
  pinMode(LED1red, OUTPUT);
  pinMode(LED2green, OUTPUT);
  digitalWrite(LED1red, LOW);
  digitalWrite(LED2green, LOW);
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

}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n------------- [Client connected] ------------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        if (data == "RED") {
          Serial.print("     * Receive from Client: ");
          Serial.println(data);
          state1 = !state1;
          digitalWrite(LED1red, state1);
        }
        if (data == "GREEN") {
          Serial.print("     * Receive from Client: ");
          Serial.println(data);
          state2 = !state2;
          digitalWrite(LED2green, state2);
        }
        else {Serial.println("Waiting for client");}
      }
    }
    delay(10);
    client.stop();
    Serial.println("------------- Disconnect, Wait 15 Seonds ---------------");
  }
}

