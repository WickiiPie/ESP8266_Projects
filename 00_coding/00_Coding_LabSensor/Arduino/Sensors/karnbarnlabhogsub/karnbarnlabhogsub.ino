#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bozz";
const char* password = "88888888";
const char* mqtt_server = "192.168.43.59";
const int mqtt_port = 1883;
const char* ClientID = "EspSubClient";
const char* Topic1 = "HW/LEDRed";
const char* Topic2 = "HW/LedLovingGreen";

WiFiClient espClient;
PubSubClient SubClient(espClient);

int green = 0;
int red = 0;
char message_buff1[100];
char message_buff2[100];
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
  SubClient.setCallback(callback1);
  SubClient.setCallback(callback2);

  //Connect to the MQTT server.
  ConnectMQTT();

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
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
    if (SubClient.connect(ClientID, NULL, NULL)) {
          Serial.println("connected");
          SubClient.setCallback(callback1);
          SubClient.setCallback(callback2);
          SubClient.subscribe(Topic1);
          SubClient.subscribe(Topic2);
    } else {
      Serial.print("failed, rc=");
      Serial.print(SubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}
void callback1(char* topic1, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic1);
  Serial.print("] ");
  int i;
  for (i = 0; i < length; i++) {
    message_buff1[i] = payload[i];
  }
  message_buff1[i] = '\0';
  String msgString1 = String(message_buff1);
  Serial.println("Payload: " + msgString1);
    digitalWrite(D2,HIGH);

  if (msgString1 == "RED") {
    red = !red; 
    digitalWrite(D2,red);
    } 
    
  if (msgString1 == "GREEN") {
    green = !green; 
    digitalWrite(D1,green);
    } 
}

void callback2(char* topic2, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic2);
  Serial.print("] ");
  int i;
  for (i = 0; i < length; i++) {
    message_buff2[i] = payload[i];
  }
  message_buff2[i] = '\0';
  String msgString = String(message_buff2);
  Serial.println("Payload: " + msgString);


  if (msgString == "GREEN") {
    green = !green; 
    digitalWrite(D1,green);
    } 
  if (msgString == "RED") {
    red = !red; 
    digitalWrite(D2,red);
    } 
    
}
