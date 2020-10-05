#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz"; 
const char* password = "88888888";
const char* mqtt_server = "192.168.43.63";
const int mqtt_port = 1883;
const char* ClientID = "EspPubClient1";
const char* Topic = "HW/LED1";

WiFiClient espClient;
PubSubClient PubClient(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(D0,INPUT_PULLUP); // ต่อสวิสขา==> D0

  //WiFi connection
  Serial.print("Connecting to ");
  Serial.println(ssid);
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
  
  //Specify the MQTT server and port.
  PubClient.setServer(mqtt_server, mqtt_port);

  //Connect to the MQTT server.
  ConnectMQTT();
}

void loop() {
  if (!PubClient.connected()) {
    ConnectMQTT();
  } 
  int sw1 = digitalRead(D0);
  if (sw1==LOW) {
    Serial.print(Topic);
    Serial.println(":  Publish 1");
    PubClient.publish(Topic, "RED");
  } else if(sw1==HIGH){
    Serial.print(Topic);
    Serial.println(":  Publish 0");
  }
  
  delay(200); //Delay 10 seconds  
}

void ConnectMQTT() {
  while (!PubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (PubClient.connect(ClientID, NULL, NULL)) {
          Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(PubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}




