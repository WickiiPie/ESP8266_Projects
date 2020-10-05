#include <ESP8266WiFi.h>
#define LED D0

const char* ssid = "MSI_XIV"; //Change to your Access Point
const char* password = "wp127001"; //Change to your AP PW
const char* host = "192.168.137.110"; //Change to your server IP address
unsigned char status_led = 0;

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (client.connect(host, 80)) {
  Serial.println("\n------------ Connect to the server ----------------");
  
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
  }
  else if(req.indexOf("/refresh")!=-1)
  {
    client.flush();
  }
}
else {
    Serial.println("+++ Cannot connect to the server +++");
  }
  Serial.println("------------ Disconnect, Wait a Second ----------");
  delay(1000); 
}
