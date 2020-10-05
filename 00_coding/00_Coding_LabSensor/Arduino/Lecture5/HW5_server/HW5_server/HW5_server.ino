#include <ESP8266WiFi.h>
#include <DHT.h>
#define LDR A0
//#define LED D0
//#define dhtpin D2
//#define DHTTYPE DHT11

//DHT dht(dhtpin,DHTTYPE);
const char* ssid = "MeowMkII";    //Access Point SSID
const char* password = "88888888";    //Access Point Password
unsigned char status_led = 0;
unsigned char control = 0;
WiFiServer server(80);

void setup() {
 // dht.begin();
  Serial.begin(115200);
//  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
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
  //if(control) status_led = analogRead(LDR) > 500;
  WiFiClient client = server.available();
delay(3);
  if (!client) {
    return;
  }

  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("Led Pls") != -1)
  {
    client.print(status_led);
    client.print("\r");
    client.stop();
    return;
  }else if (req.indexOf("/ledon") != -1 and control == 0)
  {
    status_led = 1;
    //digitalWrite(LED, HIGH);
    Serial.println("LED RED ON");
    client.print(status_led);
  }
  else if  (req.indexOf("/ledoff") != -1 and control == 0)
  {
    status_led = 0;
    //digitalWrite(LED, LOW);
    Serial.println("LED RED OFF");
    client.print(status_led);
  } 
 // if (req.indexOf("/greenoff") != -1 and control == 0)
  //{
   // status_led = 3;
  //  digitalWrite(LED2, HIGH);
   // Serial.println("LED GREEN ON");
  //}else if (req.indexOf("/greenon") != -1 and control == 0)
  //{
   // status_led = 2;
    //digitalWrite(LED2, LOW);
   // Serial.println("LED GREEN OFF");
 // }
  
  else if (req.indexOf("/refresh") != -1)
  {
    client.flush();
  } 
  else if (req.indexOf("/auto") != -1) {
    control = 1;
  } else if (req.indexOf("/manual") != -1) {
    control = 0;
  }

  //Keep the HTML code into a string
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

 
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
  web += "\t<body style=\"background: lightred;\">\r\n";
  web += "\t\t<h1>Monitor</h1>\r\n";
  web += "\t\t<p>\r\n";
  //web += "\t\t\t  Temperature:\r\n";
  //web += "\t\t\t" + String(dht.readTemperature()) + "<a href=\"/\">\r\n";
   web += "\t\t<a href=\"/refresh\">\r\n";
  web += "\t\t\t\t<button>refresh</button>\r\n";
  web += "\t\t\t</a>\r\n";
  web += "<br>\r\n";
  web += "\t\t\t  LDR value:\r\n";
  web += "\t\t\t"+ String(analogRead(LDR)) + "<a href=\"/\">\r\n";
  //web += "\t\t\t  Humidity:\r\n";
//  web += "\t\t\t" + String(dht.readHumidity()) + "<a href=\"/\">\r\n";
  //web += "\t\t\t\t<button>refresh</button>\r\n";
 // web += "\t\t\t</a>\r\n";
  web += "\t\t</p><h1>Controller</h1>\r\n";
  web += "\t\t<p>\r\n";
  web += "\t\t\t";
  if (status_led == 1)
    web += "LED On\r\n";
  else if (status_led == 0)
    web += "LED Off\r\n";

    
  web += "\t\t</p>\r\n";
  web += "\t\t<a href=\"/manual\">\r\n";
  web += "\t\t\t<button>Manual</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t\t\r\n";
  web += "\t\t<a href=\"/ledon\">\r\n";
  web += "\t\t\t<button>ledon</button>\r\n";
  web += "\t\t</a>\r\n";
  web += "\t\t<a href=\"/ledoff\">\r\n";
  web += "\t\t\t<button>ledoff</button>\r\n";
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

