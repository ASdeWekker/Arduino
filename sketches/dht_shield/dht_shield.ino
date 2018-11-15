#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WEMOS_DHT12.h>

const char* ssid = "KamerVanVerhuizing";
const char* password = "KutKarim";

ESP8266WebServer server(80);

const int led = D4;

DHT12 dht12;

void handleRoot() {
  char stuff[400];
  digitalWrite(led, 1);
  if (dht12.get() == 0) {
    Serial.println(int(dht12.cTemp));
  }

  snprintf ( stuff, 400,
"<html>\
  <head>\
    <title>esp dingen.</title>\
    <style>\
      body, html { margin: 0; padding: 0; }\
      h1 { text-align: center; font-size: 6em; }\
      p { text-align: center; font-size: 2em; }\
    </style>\
  </head>\
  <body>\
    <h1>Hmmm</h1>\
    <br>\
    <p>%02d</p>\
    <a href='/ding'>Dingen</a>\
  </body>\
</html>", int(dht12.cTemp));

  server.send ( 200, "text/html", stuff );
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
