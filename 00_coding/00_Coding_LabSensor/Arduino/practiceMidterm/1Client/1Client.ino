#include <ESP8266WiFi.h>

const char* ssid = "-XIV-5s"; //Change to your Access Point
const char* password = "wp127001"; //Change to your AP PW
const char* host = "172.20.10.10"; //Change to your server IP address
int poten = A0;
int value;
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
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
  // put your main code here, to run repeatedly:
  if (client.connect(host, 80)) {
    Serial.println("\n------------ Connect to the server ------------");
    value = analogRead(poten);
    if (value < 300) {
      Serial.println("Led1 On");
      Serial.println(value);
      client.print(value);
      client.print("\r");
      delay(1500);
    } else if (value > 300) {
      Serial.println("Led ON");
      Serial.print(value);
      client.print(value);
      client.print("\r");
      delay(1500);
    }
  } else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  client.stop();
  Serial.println("------------ Disconnect----------");
  delay(1500);
}


