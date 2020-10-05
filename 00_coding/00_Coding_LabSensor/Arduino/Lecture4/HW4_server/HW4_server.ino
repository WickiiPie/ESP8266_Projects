#include <ESP8266WiFi.h>
#include <DHT.h>
#define dhtpin D2
#define DHTTYPE DHT11

int LED1red = D0;
int LED2green = D1;
bool state1, state2;
float humid, temp;
DHT dht(dhtpin, DHTTYPE);
const char* ssid = "MSI_XIV"; //Change to your Access Point
const char* password = "wp127001"; //Change to your AP PW
WiFiServer server(80);

void setup() {
  dht.begin();
  pinMode(LED1red, OUTPUT);
  pinMode(LED2green, OUTPUT);
  digitalWrite(LED1red, LOW);
  digitalWrite(LED2green, LOW);
  Serial.begin(115200);
 
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
        if (data == "Humi") { // check data string from client
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
}



