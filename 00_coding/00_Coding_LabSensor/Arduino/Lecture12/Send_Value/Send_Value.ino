#include <ESP8266WiFi.h>
 
const char* ssid = "3bb-Wichphon"; //Change to your SSID
const char* password = "0818647157"; //Change to your PW
const char* host = "192.168.1.18"; //Change to your computer IP address
int value=0;
WiFiClient client;
 
void setup() { 
 Serial.begin(115200);
 //delay(1000); //Waiting
 //Connect to the access point==============
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
 //Serial.println("Done");

 
 //(= _ =)/
 //delay(1000);
 //========================================== 
}
 
void loop() { 
 Serial.println("loop starting");
 WiFi.begin(ssid, password);

 // Read the value and show on Serial Monitor
 value = analogRead(A0);
 Serial.print("Value = ");
 Serial.println(value);

 // Create an url to send to the web server
 // This url includes the resistance value
 String url = "";
  url += "/2017BasicPHP/Insert_Value.php";
  url += "?R1=";
  url += value;
 //If you can connect to the web server
 if (client.connect(host, 80)) {
  Serial.println("* Connect to the web server *");
  Serial.print("       Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n\r");
  Serial.println("       Waiting... 20 seconds");
  } else {
    Serial.println("+++ Cannot connect to the web server +++");
  }
   
  client.stop();
  delay(1000); //every 20 seconds
}
