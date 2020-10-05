#include <ESP8266WiFi.h>

const char* ssid = "Bozz"; //Change to your Access Point
const char* password = "88888888"; //Change to your AP PW
const char* host = "192.168.43.251"; //Change to your server IP address
int Count = 0;
int SW = D0 ;
int push ;
WiFiClient client;

void setup() {
  pinMode(SW, INPUT);

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
  //Count = Count+1;
  //If you can connect to the server
  if (client.connect(host, 80)) {
    Serial.println("\n------------ Connect to the server ------------");
    push = digitalRead(SW);
    if (push == LOW) {
      Serial.print("      * Send to Server: ");
      Serial.println(push); 
      client.print(push);
      // This will send the data to the server
    } else {
      Serial.println(".....Waiting for Switch......");
    }
  } else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  client.stop();
  Serial.println("------------ Disconnect, Wait 15 Seconds ----------");
  delay(5000); //every 15 seconds
}
