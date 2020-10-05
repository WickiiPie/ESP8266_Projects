#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz";
const char* password = "88888888";
const char* mqtt_server = "192.168.43.63"; //Computer IP address
const int mqtt_port = 1883;
const char* ClientID = "EspSubClient1";
const char* Topic = "Ex2/LED1"; //find a variable name "Ex1/LED" from the broker

WiFiClient espClient;
PubSubClient SubClient(espClient);
bool state=0;
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
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
}

void loop() {
  if (!SubClient.connected()) {
    ConnectMQTT();
  } 
  SubClient.loop(); //SubClient is a variable name //to wake up the sub everytime
}

void ConnectMQTT() {
  while (!SubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (SubClient.connect(ClientID, NULL, NULL)) {
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

void callback(char* topic, byte* payload, unsigned int length) {//payload is the data sent from the broker
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);   //payload keep in string
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    state= !state;
    digitalWrite(D0, state);   // Turn the LED on 
  } 
}


