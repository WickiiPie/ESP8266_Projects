#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz";
const char* password = "88888888";
const char* mqtt_server = "192.168.43.63"; //Computer IP address
const int mqtt_port = 1883;
const char* ClientID = "EspPubClient2";
const char* Topic1 = "Ex3/LED2"; //keep a variable name "Ex1/LED" in the broker


WiFiClient espClient;
PubSubClient PubClient(espClient);

#define sw1 D0
#define sw2 D1

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
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
  PubClient.setServer(mqtt_server, mqtt_port); //who is your broker

  //Connect to the MQTT server.
  ConnectMQTT();
}

void loop() {
  if (!PubClient.connected()) {
    ConnectMQTT();
  } 
  
  int sw2_state = digitalRead(sw2);
  if (sw2_state == LOW) {
    Serial.print(Topic1);
    Serial.println(" sw2_state : Publish 1");
    PubClient.publish(Topic1, "1"); // sent data to the broker
  } 
  if (sw2_state == HIGH) {
    Serial.print(Topic1);
    Serial.println(" sw2_state : Publish 0");
    PubClient.publish(Topic1, "0"); // sent data to the broker
  } 
  delay(1000); //Delay 10 seconds  
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
      delay(100);
    }
  }  
}




