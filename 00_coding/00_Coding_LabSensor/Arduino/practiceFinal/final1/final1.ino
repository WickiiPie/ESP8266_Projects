#include <ESP8266WiFi.h>
const char* ssid = "Bozz"; //Access Point SSID
const char* password = "88888888"; //Access Point Password
const char* host = "192.168.43.74"; //Change to your computer IP address
//WiFiServer server(80);
WiFiClient client;
int trigPin = D7;
int echoPin = D8;
int value = 0;
int buzzer = D0;///////
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);
  Serial.begin(115200);
  Serial.println("Begin a WiFi connnection");
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  long duration, dist;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 29) / 2;
  Serial.print("Distance = ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(2000);

  Serial.println("loop starting");
  WiFi.begin(ssid, password);

  // Read the value and show on Serial Monitor
  value = analogRead(A0);
  Serial.print("Value = ");
  Serial.println(value);
  Serial.println(dist);

  // Create an url to send to the web server
  // This url includes the resistance value
  String url = "";
  url += "/Final/Insert_Value.php";
  url += "?R1=";
  url += value;
  url += "&R2=";
  url += dist;
  //If you can connect to the web server
  if (client.connect(host, 80)) {
    Serial.println("* Connect to the web server *");
    Serial.print("       Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n\r");
    digitalWrite(buzzer, LOW);
    delay(5000);
    digitalWrite(buzzer, HIGH);
    Serial.println("       Waiting... 20 seconds");
  } else {
    Serial.println("+++ Cannot connect to the web server +++");
  }

  client.stop();
  delay(15000); //every 20 seconds
}

