/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

int ldr = A0;
const char* ssid = "Bozz";
const char* password = "88888888";
String ip;
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
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

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  ip = ipToString(WiFi.localIP());
  Serial.println(ip);
}
int autoMode = 0;
int val = 0;
unsigned long long timeout = 0;
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (autoMode) {
    delay(1);
    val = (analogRead(ldr) > 500);
  }
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  timeout = millis();
  while (!client.available()) {
    delay(1);
    if (millis() - timeout > 500) {
      client.flush();
      client.stop();
      Serial.println("Time out");
      return;
    }
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("Led Pls") != -1) {
    client.print(String(val)+"\r");
    client.stop();
    return;
  }
  // Match the request
  if (req.indexOf("/ledoff") != -1) {
    val = 0;
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n");
  }
  else if (req.indexOf("/ledon") != -1) {
    val = 1;
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n");
  }
  else if (req.indexOf("/autooff") != -1) {
    autoMode = 0;
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n");
  }
  else if (req.indexOf("/autoon") != -1) {
    autoMode = 1;
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n");
  }
  else if (req.indexOf("/json") != -1) {
    String s = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\r\n\t\"ldr\" : ";
    s += analogRead(ldr);
    s += ",\r\n\t";
    s += "\"auto\" : ";
    s += autoMode;
    s += ",\r\n\t";
    s += "\"led\" : ";
    s += val;
    s += "\r\n}\n";
    client.print(s);
    client.stop();
    return;
  }
  client.flush();
  if (req.indexOf(" / HTTP/") != -1) {
    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    client.print(s);
    client.print("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n<title>Untitled Document</title>\n<script src=\"http://code.jquery.com/jquery.min.js\" type=\"text/javascript\"></script>\n<script type=\"text/javascript\">\nfunction Get(yourUrl){\nvar Httpreq = new XMLHttpRequest();\nHttpreq.open(\"GET\",yourUrl,false);\nHttpreq.send(null);\nreturn Httpreq.responseText;\n}\nvar obj;\n$(document).ready(function() {\nsetInterval(function(){\nobj = JSON.parse(Get(\"http://"+ip+"/json\"));\ndocument.getElementById('ldr').innerHTML = obj.ldr\nif (obj.auto == 0) {\n$('#autoBox').prop('checked', false);\n}\nelse {\n$('#autoBox').prop('checked', true);\n}\nif (obj.led == 0) {\n$('body').removeClass('night');\n}\nelse {\n$('body').addClass('night');\n}\n}, 1000);\n});\n$(document).ready(function() {\n$('.bulb-light').click(function() {\nif (obj.auto == 1) return;\nif (obj.led == 0) {\nGet(\"http://"+ip+"/ledon\")\n}\nelse{\nGet(\"http://"+ip+"/ledoff\")\n}\n});\n});\n$(document).ready(function() {\n$('body > label > span').click(function() {\nif (obj.auto == 0) {\nGet(\"http://"+ip+"/autoon\")\n}\nelse{\nGet(\"http://"+ip+"/autooff\")\n}\n});\n});\n</script>\n<style type=\"text/css\">\nbody { background: #FFF; }\n.switch {\nposition: relative;\ndisplay: inline-block;\nwidth: 60px;\nheight: 34px;\n}\n.switch input {display:none;}\n.slider {\nposition: absolute;\ncursor: pointer;\ntop: 0;\nleft: 0;\nright: 0;\nbottom: 0;\nbackground-color: #ccc;\n-webkit-transition: .4s;\ntransition: .4s;\n}\n.slider:before {\nposition: absolute;\ncontent: \"\";\nheight: 26px;\nwidth: 26px;\nleft: 4px;\nbottom: 4px;\nbackground-color: white;\n-webkit-transition: .4s;\ntransition: .4s;\n}\ninput:checked + .slider {\nbackground-color: #2196F3;\n}\ninput:focus + .slider {\nbox-shadow: 0 0 1px #2196F3;\n}\ninput:checked + .slider:before {\n-webkit-transform: translateX(26px);\n-ms-transform: translateX(26px);\ntransform: translateX(26px);\n}\n.slider.round {\nborder-radius: 34px;\n}\n.slider.round:before {\nborder-radius: 50%;\n}\n.night { background: #000; }\n.container {\ntext-align: center;\nmargin: 20px auto;\n}\nh2 { color: #CCC; }\n.bulb-light {\nposition: relative;\nborder: 0;\nbackground: transparent;\nmargin: 0 auto !important;\npadding: 0 !important;\ncursor: pointer;\ndisplay: block;\nz-index: 1;\n}\n#light {\n-moz-opacity: 0;\n-khtml-opacity: 0;\nopacity: 0;\nposition: absolute;\ntop: 5px;\nleft: 0;\nright: 0;\nbox-shadow: 0px 0px 500px rgba(255,210,00,1), inset 0px 0px 500px 90px rgba(255,210,00,0.42);\n-moz-box-shadow: 0px 0px 500px rgba(255,210,00,1), inset 0px 0px 500px 90px rgba(255,210,00,0.42);\n-webkit-box-shadow: 0px 0px 500px rgba(255,210,00,1), inset 0px 0px 500px 90px rgba(255,210,00,0.42);\n-moz-border-radius: 999px;");
    client.print("\n-webkit-border-radius: 999px;\n-khtml-border-radius: 999px;\nborder-radius: 999px;\nwidth: 290px;\nheight: 290px;\nbackground: none;\nmargin: 0 auto;\ntext-align: center;\nz-index: 2;\n}\n#bulb {\nopacity: 1;\nz-index: 3;\n}\n.bulb-top {\nposition: relative;\nborder: 0;\nwidth: 300px;\nheight: 300px;\nmargin: 0 auto;\npadding: 0;\n-moz-border-radius: 999px;\n-webkit-border-radius: 999px;\n-khtml-border-radius: 999px;\nborder-radius: 999px;\nbackground: #E7E7E7;\nbox-shadow: inset 0px 10px 15px -5px rgba(10,30,60,0.1);\n-moz-box-shadow: inset 0px 10px 15px -5px rgba(10,30,60,0.1);\n-webkit-box-shadow: inset 0px 20px 40px -10px rgba(10,30,60,0.1);\n}\n.reflection {\nposition: absolute;\ntop: 50px;\nleft: 50px;\nbackground: rgba(255,255,255,0.8);\nwidth: 50px;\nheight: 50px;\n-moz-border-radius: 999px 400px;\n-webkit-border-radius: 999px 400px;\n-khtml-border-radius: 999px 400px;\nborder-radius: 999px 400px;\n}\n.bulb-middle-1 {\nmargin: -75px auto 0 auto;\nwidth: 190px;\nheight: 0;\nborder-left: 35px solid transparent;\nborder-right: 35px solid transparent;\nborder-top: 55px solid #E7E7E7;\n}\n.bulb-middle-2 {\nmargin: -22px auto 0 auto;\nwidth: 178px;\nheight: 0;\nborder-left: 19px solid transparent;\nborder-right: 19px solid transparent;\nborder-top: 50px solid #E7E7E7;\n}\n.bulb-middle-3 {\nmargin: -20px auto 0 auto;\nwidth: 182px;\nheight: 0;\nborder-left: 5px solid transparent;\nborder-right: 5px solid transparent;\nborder-top: 30px solid #E7E7E7;\n}\n.bulb-bottom {\nwidth: 184px;\nheight: 65px;\nmargin: -8px auto 0 auto;\npadding: 0;\n-moz-border-radius: 0 0 999px 999px;\n-webkit-border-radius: 0 0 999px 999px;\n-khtml-border-radius: 0 0 999px 999px;\nborder-radius: 0 0 999px 999px;\nbackground: #E7E7E7;\nbox-shadow: inset 0px -10px 14px -7px rgba(10,30,60,0.1);\n-moz-box-shadow: inset 0px -10px 14px -7px rgba(10,30,60,0.1);\n-webkit-box-shadow: inset 0px -10px 14px -7px rgba(10,30,60,0.1);\n}\n#base { position:relative; z-index: 2; }\n.screw-top {\nmargin: -18px auto -4px auto;\npadding: 0;\nwidth: 132px;\nheight: 0;\nborder-left: 15px solid transparent;\nborder-right: 15px solid transparent;\nborder-top: 21px solid #D3D3D3;\n-moz-border-radius: 999px;\n-webkit-border-radius: 999px;\n-khtml-border-radius: 999px;\nborder-radius: 999px;\n}\n.screw-a {\nbackground: #DDD;\nwidth: 150px;\nheight: 15px;\n-moz-border-radius: 999px;\n-webkit-border-radius: 999px;\n-khtml-border-radius: 999px;\nborder-radius: 999px;\nmargin: -1px auto 0px;\npadding: 0;\ntransform: rotate(-3deg);\n-ms-transform: rotate(-3deg);\n-webkit-transform: rotate(-3deg);\n/*\nbox-shadow: inset 0px -2px 10px 0px rgba(10,30,60,0.2),\ninset -20px 0px 60px -20px rgba(0,0,0,0.5);\n-moz-box-shadow: inset 0px -2px 10px 0px rgba(10,30,60,0.2),\ninset -20px 0px 60px -20px rgba(0,0,0,0.5);\n-webkit-box-shadow: inset 0px -2px 10px 0px rgba(10,30,60,0.2),\ninset -20px 0px 60px -20px rgba(0,0,0,0.5);\n*/\n}\n.screw-b {\nbackground: #D9D9D9;\nwidth: 135px;\nheight: 15px;");
    client.print("\nmargin: -1px auto 0px;\npadding: 0;\ntransform: rotate(-3deg);\n-ms-transform: rotate(-3deg);\n-webkit-transform: rotate(-3deg);\n/*\nbox-shadow: inset -15px 0px 55px -20px rgba(0,0,0,0.5);\n-moz-box-shadow: inset -15px 0px 55px -20px rgba(0,0,0,0.5);\n-webkit-box-shadow: inset -15px 0px 55px -20px rgba(0,0,0,0.5);\n*/\n}\n.screw-c2 {\nbackground: #DDD;\nwidth: 135px;\nheight: 20px;\nmargin: -1px auto 0px;\npadding: 0;\n-moz-border-radius: 0 0 999px 999px;\n-webkit-border-radius: 0 0 999px 999px;\n-khtml-border-radius: 0 0 999px 999px;\nborder-radius: 0 0 999px 999px;\ntransform: rotate(-3deg);\n-ms-transform: rotate(-3deg);\n-webkit-transform: rotate(-3deg);\n}\n.screw-c {\nmargin: -1px auto 0px;\npadding: 0;\nwidth: 78px;\nheight: 0;\nborder-left: 30px solid transparent;\nborder-right: 30px solid transparent;\nborder-top: 20px solid #DDD;\n-moz-border-radius: 8px;\n-webkit-border-radius: 8px;\n-khtml-border-radius: 8px;\nborder-radius: 8px;\ntransform: rotate(-3deg);\n-ms-transform: rotate(-3deg);\n-webkit-transform: rotate(-3deg);\n}\n.screw-d {\nmargin: 0 auto;\npadding: 0;\nwidth: 15px;\nheight: 0;\nborder-left: 30px solid transparent;\nborder-right: 30px solid transparent;\nborder-top: 15px solid #444;\ntransform: rotate(-3deg);\n-ms-transform: rotate(-3deg);\n-webkit-transform: rotate(-3deg);\n}\n.night #light {\n-moz-opacity: 1;\n-khtml-opacity: 1;\nopacity: 1;\n}\nbody, .bulb-top, .bulb-bottom {\n-webkit-transition: background 0.5s ease-in-out;\n-moz-transition: background 0.5s ease-in-out;\n-o-transition: background 0.5s ease-in-out;\ntransition: background 0.5s ease-in-out;\n}\n.bulb-middle-1, .bulb-middle-2, .bulb-middle-3 {\n-webkit-transition: border 0.5s ease-in-out;\n-moz-transition: border 0.5s ease-in-out;\n-o-transition: border 0.5s ease-in-out;\ntransition: border 0.5s ease-in-out;\n}\n.night .bulb-top, .night .bulb-bottom { background: #FE3; }\n.night .bulb-middle-1 {border-top: 55px solid #FE3; }\n.night .bulb-middle-2 {border-top: 50px solid #FE3; }\n.night .bulb-middle-3 {border-top: 30px solid #FE3; }\n</style>\n</head>\n<body>\n<div class=\"container\">\n<h2>Light bulb</h2>\n<a class=\"bulb-light\">\n<div id=\"light\"></div>\n<div id=\"bulb\">\n<div class=\"bulb-top\">\n<div class=\"reflection\"></div>\n</div>\n<div class=\"bulb-middle-1\"></div>\n<div class=\"bulb-middle-2\"></div>\n<div class=\"bulb-middle-3\"></div>\n<div class=\"bulb-bottom\"></div>\n</div>\n<div id=\"base\">\n<div class=\"screw-top\"></div>\n<div class=\"screw-a\"></div>\n<div class=\"screw-b\"></div>\n<div class=\"screw-a\"></div>\n<div class=\"screw-b\"></div>\n<div class=\"screw-a\"></div>\n<div class=\"screw-b\"></div>\n<div class=\"screw-c\"></div>\n<div class=\"screw-d\"></div>\n</div>\n</a>\n</div>\n<h2>Light intensity</h2>\n<div style=\"color:gray\" id = \"ldr\">&nbsp;</div>\n<h2>Mode Auto</h2>\n<!-- <div style=\"color:gray\" id = \"auto\">&nbsp;</div> -->\n<label class=\"switch\">\n");
    client.print("<input id = \"autoBox\" type=\"checkbox\" onclick=\"return false;\">\n<span class=\"slider round\"></span>\n<!-- <div id = \"autoBox\"></div> -->\n</label>\n</body>\n</html>\n\n");
  }
  // Send the response to the client
  //client.print(s);
  client.stop();
  delay(1);
  Serial.println("Client disonnected");

}
String ipToString(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

