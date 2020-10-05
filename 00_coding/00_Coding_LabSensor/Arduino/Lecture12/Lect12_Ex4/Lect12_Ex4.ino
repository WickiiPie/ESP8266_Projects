#include <ESP8266WiFi.h>
const char* ssid = "MeowMkII"; //Access Point SSID
const char* password = "88888888"; //Access Point Password
WiFiServer server(80);
int trigPin = D7;
int echoPin = D8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  long duration, dist;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration/29)/2;
  Serial.print("Distance = ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(2000);
   
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  Serial.print(analogRead(A0));
  while (!client.available())
  {
    delay(1);
  }

  //Create a HTTP response as the String variable named "web"
  //Header of this HTTP response
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  //Body of this HTTP response
  web += "Resistance = ";
  web += String(analogRead(A0));
  web += "  Distance =  ";
  web += String(dist);
  client.print(web);

  
}



