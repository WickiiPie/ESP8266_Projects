#include <ESP8266WiFi.h>

const char* ssid = "MyAccessPoint"; //Change to your Access Point
const char* password = "12345678"; //Change to your AP PW
const char* host = "192.168.4.1"; //Change to your server IP address
int Count = 0;
int SW1yellow = D0 ;
int SW2white = D2 ;
int push1,push2 ;
WiFiClient client;

void setup() {
  pinMode(SW1yellow, INPUT);
  pinMode(SW2white, INPUT);
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
    push1 = digitalRead(SW1yellow);
    push2 = digitalRead(SW2white);
    if (push1 == LOW) {
      Serial.print("      * Send to Server: ");
      Serial.println(push1);
      client.print("RED");
      client.print('\r');
      delay(100);
      // This will send the data to the server
    }
    
    if (push2 == HIGH) {
      Serial.print("      * Send to Server: ");
      Serial.print("green");
      Serial.println(push2);
      client.print("GREEN");
      client.print('\r');
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
