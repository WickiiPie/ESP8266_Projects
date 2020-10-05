#include <ESP8266WiFi.h>

const char* ssid = "-XIV-5s"; //Change to your Access Point
const char* password = "wp127001"; //Change to your Access Point PW
int led = D0;
int led1=D1;
bool state;


WiFiServer server(80);
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
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
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();
  if (client) {
    
    Serial.println("\n------------- [Client connected] ------------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        if (data.toInt() > 300) {
          //state=!state;
          digitalWrite(led, HIGH);
          digitalWrite(led1, LOW);
          Serial.print("   * Receive from Client: ");
          Serial.println(data);
          delay(500);
        }else if(data.toInt()<300){
          digitalWrite(led,LOW);
          digitalWrite(led1, HIGH);
          Serial.print("   * Receive from Client: ");
          Serial.println(data);
          delay(500);
        }
      }
    }
    delay(500);
    client.stop();
    Serial.println("--------------- Disconnected---------------");
  }
}
