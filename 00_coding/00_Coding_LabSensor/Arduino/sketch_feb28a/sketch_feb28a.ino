#include <ESP8266WiFi.h>
#include <DHT.h>
DHT dht(D2, DHT11);
int led0 = D0;
int led1 = D1;


int LDR = A0;
const char* ssid = "Bozz"; //Access Point SSID
const char* password = "88888888"; //Access Point Password
WiFiServer server(80);
unsigned char statusled0 = 0;
unsigned char statusled1 = 0;



void setup() {
  // put your setup code here, to run once:
  void setup() {
    dht.begin();
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
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

}

void loop() {
  // put your main code here, to run repeatedly:
 WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }


















//==========================
 String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>Sensor Monitor</h1>\r\n";
  web += "<p>\r\n";
  web += "Temp = ";
  web += String(dht.readTemperature());
  //web += " C";
  web += "<p>\r\n";
  web += "Humidity = ";
  web += String(dht.readHumidity());
  //web += " %";
  web += "</p>\r\n";
  web += "Light = ";
  web += String(analogRead(A0));
  //web += " C";
  web += "<p>\r\n";
  //========================================
  web += "<h1>Controller</h1>\r\n";
  web += "<p>\r\n";

  if (status_red == 0)
    web += "RED ON\r\n";
  else if (status_red == 1)
    web += "RED OFF\r\n";

  web += "</p>\r\n";
  web += "<br>\r\n";
  if (status_green == 0)
    web += "Green ON\r\n";
  else if (status_green == 1)
    web += "Green OFF\r\n";

  if (status_buzzer == 0)
    web += "buzzer ON\r\n";
  else if (status_buzzer == 1)
    web += "buzzer OFF\r\n";

  web += "</p>\r\n";
  web += "<p>\r\n";


  web += "<a href=\"/green\">\r\n";
  web += "<button>Green</button>\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  //=========================
  web += "<a href=\"/red\">\r\n";
  web += "<button>Red</button>\r\n";
  web += "</a>\r\n";

  web += "<a href=\"/buzzer\">\r\n";
  web += "<button>buzzer</button>\r\n";
  web += "</a>\r\n";


  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
    
  
}
