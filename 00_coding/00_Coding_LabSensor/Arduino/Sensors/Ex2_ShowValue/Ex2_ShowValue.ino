#include <ESP8266WiFi.h>
#include <DHT.h>
const char* ssid = "Engineering2"; //Access Point SSID
const char* password = "engineeringlab"; //Access Point Password
WiFiServer server(80);
DHT dht(D2, DHT11);

void setup() {
  dht.begin();
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
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }

  //Keep the HTML in to the String variable named "web"
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>Weather Status</h1>\r\n";
  web += "<p>\r\n";
  web += "Temperature = ";
  web += String(dht.readTemperature());
  web += " C";
  web += "<p>\r\n";
  web += "Humidity = ";
  web += String(dht.readHumidity());
  web += " %";
  web += "</p>\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}

