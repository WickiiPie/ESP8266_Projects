#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz";
const char* password = "88888888";
const char* mqtt_server = "m11.cloudmqtt.com"; //MQTT Broker
const int mqtt_port = 16425;
const char* mqtt_user = "iypwhpdg";
const char* mqtt_pass = "c6ZTPud89GFo";
const char* ClientID = "EspSubClient8888";
const char* Topic = "Ex4/8888";

WiFiClient espClient;
PubSubClient PubClient(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println();

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
  //PubClient.setCallback(callback);

  //Connect to the MQTT server.
  ConnectMQTT();
}

void loop() {
  if (!PubClient.connected()) {
    ConnectMQTT();
  } 
  int R_Value = analogRead(A0);
  if (R_Value>500) {
    Serial.print(Topic);
    Serial.println(":  Publish 1");
    PubClient.publish(Topic, "1");
  } else {
    Serial.print(Topic);
    Serial.println(":  Publish 0");
    PubClient.publish(Topic, "0");
  }
  delay(10000); //Delay 10 seconds  
}

void ConnectMQTT() {
  while (!PubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (PubClient.connect(ClientID, mqtt_user, mqtt_pass)) {
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




