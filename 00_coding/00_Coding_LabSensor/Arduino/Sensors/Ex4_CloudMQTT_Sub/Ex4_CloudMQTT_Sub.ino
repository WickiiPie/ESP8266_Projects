#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz";
const char* password = "88888888";
const char* mqtt_server = "m11.cloudmqtt.com"; //MQTT Broker
const int mqtt_port = 16425;
const char* mqtt_user = "iypwhpdg";
const char* mqtt_pass = "c6ZTPud89GFo";
const char* ClientID = "EspSubClient7777";
const char* Topic = "Ex4/8888";

WiFiClient espClient;
PubSubClient SubClient(espClient);

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
  SubClient.setServer(mqtt_server, mqtt_port);
  SubClient.setCallback(callback);

  //Connect to the MQTT server.
  ConnectMQTT();

  //Set digital pin
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
}

void loop() {
  if (!SubClient.connected()) {
    ConnectMQTT();
  } 
  SubClient.loop(); 
}

void ConnectMQTT() {
  while (!SubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (SubClient.connect(ClientID, mqtt_user, mqtt_pass)) {
          Serial.println("connected");
          SubClient.setCallback(callback);
          SubClient.subscribe(Topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(SubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(D5, HIGH);   // Turn the LED on 
  } else {
    digitalWrite(D5, LOW);  // Turn the LED off
  }
}


