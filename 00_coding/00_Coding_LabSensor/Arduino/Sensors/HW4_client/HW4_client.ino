
#include <ESP8266WiFi.h>

const char* ssid = "Bozz"; //Change to your Access Point
const char* password = "88888888"; //Change to your AP PW
const char* host = "192.168.43.251"; //Change to your server IP address
int Count = 0;
int SW1yellow = D0 ;
int SW2white = D1 ;
int push1, push2;
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
  //WiFiServer server = client.available();
  if (client.connect(host, 80)) {
    Serial.println("\n------------ Connect to the server ----------------");
    push1 = digitalRead(SW1yellow);
    push2 = digitalRead(SW2white);
    if (push1 == LOW) {
      Serial.print("    * Send to Server: ");
      Serial.println("Humi");
      client.print("Humi");
      while (client.connected()) {
        if (client.available()) {
          String dataH = client.readStringUntil('\r');
          Serial.print("    * Receive from Server: ");
          Serial.print("  Humidity : ");
          Serial.print(dataH);
          Serial.println(" %");
        }
      }
    }
    // This will send the data to the server
    if (push2 == LOW) {
      Serial.print("    * Send to Server: ");
      Serial.println("Temp");
      client.print("Temp");
      while (client.connected()) {
        if (client.available()) {
          String dataT = client.readStringUntil('\r');
          Serial.print("    * Receive from Server: ");
          Serial.print("  Temperature : ");
          Serial.print(dataT);
          Serial.println(" C");
        }
      }
    } 
//    else {
//      Serial.println(".....Waiting for Switch......");
//    }
    client.stop();

  }
  else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  Serial.println("------------ Disconnect, Wait 15 Seconds ----------");
  delay(5000); //every 15 seconds
}
