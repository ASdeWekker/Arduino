#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define led D4

ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from mij");
  digitalWrite(led, 0);
}

void setup() {
  Serial.begin(230400);
  pinMode(led, OUTPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect("(_)_)::::::::D~~~", "wemos");

  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
