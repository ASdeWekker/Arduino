#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define ledpin D4

ESP8266WebServer server(80);

// Index page.
void handleRoot() {
  String html ="<html> <head> <meta name=\"viewport\" content=\"width=device width, initial-scale=1\"> <title>Ding</title> </head> <body> <h1>Dingetje</h1> <p><a href=\"http://192.168.1.71/led?led=aan\">Aan</a></p> <p><a href=\"http://192.168.1.71/led?led=uit\">Uit</a></p> <p><a href=\"http://192.168.1.71/led?led=toggle\">Toggle</a></p> </body> </html>";
  server.send(200, "text/html", html);
}

// Led request handling.
void ledje() {
  if (server.arg("led") == "aan") {
    digitalWrite(ledpin, HIGH);
  } else if (server.arg("led") == "uit") {
    digitalWrite(ledpin, LOW);
  } else if (server.arg("led") == "toggle") {
    if (digitalRead(ledpin) == HIGH) {
      digitalWrite(ledpin, LOW);
    } else {
      digitalWrite(ledpin, HIGH);
    }
  }
}

void setup() {
  // Setup basic stuff.
  Serial.begin(230400);
  pinMode(ledpin, OUTPUT);

  // Wifi manager setup.
  WiFiManager wifiManager;
  wifiManager.autoConnect("(_)_)::::::::D~~~", "password");

  // Wifi/server stuff.
  Serial.println(WiFi.localIP());
  server.on("/led", ledje);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Call the server
  server.handleClient();
}
