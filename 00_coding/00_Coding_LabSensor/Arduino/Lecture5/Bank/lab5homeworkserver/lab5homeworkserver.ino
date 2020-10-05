#include <ESP8266WiFi.h>

const char* ssid = "MSI_XIV"; //Change to your Access Point
const char* password = "wp127001"; //Change to your Access Point PW

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
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
  Serial.print("connectd to :");
  Serial.println(ssid);
  server.begin(); //Start working as a server
  Serial.println("Server starts.");
}
int val=0;
int status_led=0;
int autom=0, manual=0;
void loop() {
  WiFiClient client = server.available();
  if (!client) return;
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\r');
        int ldr = analogRead(A0); 
        Serial.println(data);
        client.flush();
        if (data.indexOf("/refresh")!= -1)client.flush(); 
        if (data.indexOf("/auto") != -1){
          manual=0;
          autom=1;        
        }
        if (autom==1 and ldr>500)val=1;
        if (autom==1 and ldr<500)val=0; 
        if (data.indexOf("/manual")!=-1){
          manual=1;
          autom=0;
        }
        if (data.indexOf("/ledoff") != -1 and manual==1)val=0;  
        if (data.indexOf("/ledon") != -1 and manual==1)val=1;
        if(data=="req"){
         client.print(val);
         client.print('\r');
         client.flush();
         client.stop(); 
         return;
        }
        String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        web += "<html>\r\n";
        web += "<body>\r\n";
        web += "<h1>LED Status</h1>\r\n";
        web += "<p>\r\n";
        web += "Light Intensity:\r\n";
        web += String(analogRead(A0));
        web += "<a href=\"/refresh\">\r\n";
        web += "<button>Refresh</button>\r\n";
        web += "</a>\r\n";
        web += "<h1>Home Controller</h1>\r\n";
        web += "<p>\r\n";
        web += "<a href=\"/auto\">\r\n";
        web += "<button>Auto</button>\r\n";
        web += "<a href=\"/manual\">\r\n";
        web += "<button>Manual</button>\r\n";
        web += "<p>\r\n";
        if(status_led==1)
          web += "LED On\r\n";
        else
          web += "LED Off\r\n";
        web += "</p>\r\n";
        web += "<p>\r\n";
        web += "<a href=\"/ledon\">\r\n";
        web += "<button>LED On</button>\r\n";
        web += "</a>\r\n";
        web += "</p>\r\n";
        web += "<a href=\"/ledoff\">\r\n";
        web += "<button>LED Off</button>\r\n";
        web += "</a>\r\n";
        web += "</body>\r\n";
        web += "</html>\r\n";
        client.print(web);
        client.stop();

      }
    }
  
}

