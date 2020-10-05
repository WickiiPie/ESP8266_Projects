#include <ESP8266WiFi.h>

const char* ssid     = "Bozz";
const char* password = "88888888";
unsigned char status_led=0;

const char* host = "192.168.43.3";
int LED = D0;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(D0, OUTPUT);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String req = client.readStringUntil('\r');         
  Serial.println(req);              
  client.flush();
  if (req.indexOf("/ledoff") != -1)         
  {
    status_led=0;                   
    digitalWrite(LED,LOW);          
    Serial.println("LED OFF");
  }
  else if(req.indexOf("/ledon") != -1)      
  {
    status_led=1;                   
    digitalWrite(LED,HIGH);         
    Serial.println("LED ON");
  }else if(req.indexOf("/refresh")!=-1)
  {
    client.flush();
  }
}
