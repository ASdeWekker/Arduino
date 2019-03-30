#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN D4
bool check = LOW;

ESP8266WebServer server(80);

CRGB leds[NUM_LEDS];

// Function for choosing the strip's color.
void stripColor(int r, int g, int b) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(r,b,g);
        FastLED.show();
        delayMicroseconds(1);
    }
}

// Led request handling.
void ledControl() {
    if (server.arg("led") == "on") {
        stripColor(0,255,255);
        check = HIGH;
    } else if (server.arg("led") == "off") {
        stripColor(0,0,0);
        check = LOW;
    } else if (server.arg("led") == "toggle") {
        if (check == HIGH) {
            stripColor(0,0,0);
            check = LOW;
        } else {
            stripColor(0,255,255);
            check = HIGH;
        }
    }
    server.send(200, "text/plain", "Processed.\n");
}

void setup() {
    // Setup basic stuff.
    Serial.begin(230400);


    // Wifi manager setup.
    WiFiManager wifiManager;
    wifiManager.autoConnect("(_)_)::::::::D~~~", "password");
    Serial.println(WiFi.localIP());

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(100);

    server.on("/led", ledControl);
    server.begin();
    Serial.println("Server started.");
}

void loop() {
    // Call the server
    server.handleClient();
}
