/*  Ik wil dat de strip via led wordt aangeroepen.
    En dat je dan zelf extra argumenten mee kan geven
    zoals aan/uit, kleur en fade aan/uit of fade
    naar een andere kleur.

    Het lijkt mij daarnaast handiger om de technische
    en opstartcode in die bestand te houden en om dan
    voor de ledstrip controle functie een extra
    ledstrip-desk.h bestand aan te maken en die te
    includen.

    Daarnaast wil ik de volgende functies/argumenten
    implementeren.
    stripColor: gebruikt het color argument:
    - gooi er drie kleurcodes in die door de strip
    toegepast worden, hier moet nog een integratie
    met fade bij zitten.
    ledControl: gebruikt het aan/uit argument:
    - zet de strip uit met het command on, off
    of toggle. Integreer dit met fade om het uit
    te laten faden. Moet even nagedacht worden
    of er altijd een fade functie in moet zitten,
    ik ga het gewoon testen en kijken wat ik het
    meest gebruik.
    fade: laat de strip aan/uit of naar een andere
    kleur faden:
    - Integreer dit met stripColor en ledControl,
    wanneer er een andere vooringestelde kleur wordt
    geselecteerd zoals blauw kan dit met een fade
    veranderen. Ook kan er voor het aan en uitgaan
    een fade worden toegepast.

    Alle functienamen kunnen nog veranderd worden.
*/

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
