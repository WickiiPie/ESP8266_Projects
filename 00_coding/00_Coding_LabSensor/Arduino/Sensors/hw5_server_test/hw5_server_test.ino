#include <ESP8266WiFi.h>
#define LDR A0
const char* ssid = "MSI_XIV";    //Access Point SSID
const char* password = "wp127001";    //Access Point Password
unsigned char status_led=0;
WiFiServer server(80);              

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);             
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
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();   
  
  if (!client) {            
    return;
  }
   
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
//Keep the HTML code into a string
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>Home Monitor</h1>\r\n";
  web += "<p>\r\n";
  web += "Light Intensity:\r\n";
  web += String(analogRead(LDR)-1);
  web += "<a href=\"/refresh\">\r\n";
  web += "<button>refresh</button>\r\n";
  web += "</a>\r\n";
  web += "<h1>Home Controller</h1>\r\n";
  web += "<p>\r\n";
  if(status_led==1)
      web += "LED On\r\n";
  else
      web += "LED Off\r\n";
  web += "</p>\r\n";
  //web += "<p>\r\n";
  
  web += "<a href=\"/ledon\">\r\n";
  web += "<button>LED On</button>\r\n";
  web += "</a>\r\n";
  //web += "</p>\r\n";
  web += "<a href=\"/ledoff\">\r\n";
  web += "<button>LED Off</button>\r\n";
  web += "</a>\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}




