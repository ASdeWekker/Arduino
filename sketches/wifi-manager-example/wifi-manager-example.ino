#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define ledpin D2

ESP8266WebServer server(80);

// Index page.
void handleRoot() {
  String html ="<html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <title>LED</title> </head> <body> <h1>LEDje</h1> <p><button onclick=\"aan()\">Aan</button></p> <p><button onclick=\"uit()\">Uit</button></p> <p><button onclick=\"toggle()\">Toggle</button></p> <script type=\"text/javascript\"> var xhttp = new XMLHttpRequest(); function aan() { xhttp.open(\"GET\", \"http://192.168.1.71/led?led=aan\", true); xhttp.send(); } function uit() { xhttp.open(\"GET\", \"http://192.168.1.71/led?led=uit\", true); xhttp.send(); } function toggle() { xhttp.open(\"GET\", \"http://192.168.1.71/led?led=toggle\", true); xhttp.send(); } </script> </body> </html>";
  server.send(200, "text/html", html);
}

// Led request handling.
void ledje() {
  if (server.arg("led") == "aan") {
    digitalWrite(ledpin, HIGH);
    Serial.println("Led aan");
  } else if (server.arg("led") == "uit") {
    digitalWrite(ledpin, LOW);
    Serial.println("Led uit");
  } else if (server.arg("led") == "toggle") {
    if (digitalRead(ledpin) == HIGH) {
      digitalWrite(ledpin, LOW);
      Serial.println("Toggle uit");
    } else {
      digitalWrite(ledpin, HIGH);
      Serial.println("Toggle aan");
    }
  }

  server.send(200, "text/plain", "Verwerkt");
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
