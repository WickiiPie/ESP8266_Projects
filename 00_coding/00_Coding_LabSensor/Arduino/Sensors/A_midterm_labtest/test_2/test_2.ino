#include <ESP8266WiFi.h>
#include <DHT.h>
#define dhtpin D1
#define DHTTYPE DHT11

int LED1red = D0;
int LED2green = D1;
bool state1, state2;
float humid, temp;
DHT dht(dhtpin, DHTTYPE);
const char* ssid = "Bozz"; //Change to your Access Point
const char* password = "88888888"; //Change to your AP PW
WiFiServer server(80);

void setup() {
  dht.begin();
  pinMode(LED1red, OUTPUT);
  pinMode(LED2green, OUTPUT);
  digitalWrite(LED1red, LOW);
  digitalWrite(LED2green, LOW);
  Serial.begin(115200);
  //  Serial.print("Setting soft-AP ... ");
  //  boolean result = WiFi.softAP("MyAccessPoint", "12345678");
  //  if (result == true) {
  //    Serial.println("Ready");
  //  } else {
  //    Serial.println("Failed!");
  //  }
  //IPAddress apip = WiFi.softAPIP();
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
  server.begin(); //Start working as a server
  Serial.println("Server starts.");
  //Serial.print("Server IP Address: ");
  //Serial.println(WiFi.softAPIP());

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  WiFiClient client = server.available();
  if (client) {
    Serial.println("\n------------- [Client connected] ------------------------");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        if (data == "Humi") {
          Serial.print("     * Receive from Client : ");
          Serial.println(data);
          //humid = getHumidity();
          //Serial.println("---------------------------------");
          Serial.print("     * Humidity : ");
          Serial.print(h);
          Serial.println(" %");
          client.print(h);
          state1 = !state1;
          digitalWrite(LED1red, state1);
        }
        if (data == "Temp") {
          Serial.print("     * Receive from Client : ");
          Serial.println(data);
          //temp = getTemperature();
          //Serial.println("---------------------------------");
          Serial.print("     * Tempurature : ");
          Serial.print(t);
          Serial.println(" C");
          client.print(t);
          state2 = !state2;
          digitalWrite(LED2green, state2);
        }
        client.stop();
      }
    }
    delay(10);
    Serial.println("------------- Disconnect, Wait 15 Seconds ---------------");
  }

  /*  WiFiClient client = server.available();
    if (client) {
      Serial.println("\n--------- [Client connected]----------");
      while (client.connected()) {
        if (client.available()) {
          String data = client.readStringUntil('\r');
          Serial.print("   * Receive from Client: ");
          Serial.println(data);
          Serial.print("   * Send to Client: ");
          Serial.println(data.toInt() + 1);
          client.print(data.toInt() + 1);
          client.stop();
          Serial.println("--------- Disconnect, Wait 15 Seconds ----------");
        }*/
  //Keep the HTML code into a string
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

  //ฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝฝ
  web += "<html>\r\n";
  web += "\t<head>\r\n";
  web += "\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\">\r\n";
  web += "\t\t<title>Homework 5</title><link rel=\"icon\" href=\"/favicon.ico\" type=\"image/x-icon\">\r\n";
  web += "\t\t<style type=\"text/css\">\r\n";
  web += "\t\t\ta {\r\n";
  web += "\t\t\t\ttext-decoration: none;\r\n";
  web += "\t\t\t}\r\n";
  web += "\t\t</style>\r\n";
  web += "\t</head>\r\n";
  web += "\t<body style=\"background: lightpink;\">\r\n";
  web += "\t\t<h1>Sensor Monitor</h1>\r\n";
  web += "\t\t<p>\r\n";
  //==========================Temp=====================
  web += "\t\t\tTemp =\r\n";
  web += "\t\t\t" + String(dht.readTemperature()) + "<a href=\"/\">\r\n";
  //web += "\t\t\t\t<button>refresh</button>\r\n";
  web += "\t\t\t</a>\r\n";
  //==========================Humi=====================
  web += "\t\t\tHumidity =\r\n";
  web += "\t\t\t" + String(dht.readHumidity()) + "<a href=\"/\">\r\n";
  //web += "\t\t\t\t<button>refresh</button>\r\n";
  web += "\t\t\t</a>\r\n";
  web += "\t\t</p><h1>Controller</h1>\r\n";
  web += "\t\t\tHumidity =\r\n";

  web += "\t\t<p>\r\n";
  web += "\t\t\t";
//  if (status_led == 1)
//    web += "LED On\r\n";
//  else if (status_led == 0)
//    web += "LED Off\r\n";
  web += "\t\t</p>\r\n";
  web += "\t\t<a href=\"/manual\">\r\n";
  web += "\t\t\t<button>Manual</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t\t\r\n";
  web += "\t\t<a href=\"/ledon\">\r\n";
  web += "\t\t\t<button>LED On</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t\t<a href=\"/ledoff\">\r\n";
  web += "\t\t\t<button>LED Off</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t\t<br>\r\n";
  web += "\t\t<br>\r\n";
  web += "\t\t<a href=\"/auto\">\r\n";
  web += "\t\t\t<button>Auto</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t</body>\r\n";
  web += "</html>\r\n\r\n\r\n\r\n";
  client.print(web);
  client.flush();
  client.stop();
}





