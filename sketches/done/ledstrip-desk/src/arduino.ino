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
	$stripColor: gebruikt het color argument:
	- gooi er drie kleurcodes in die door de strip
	toegepast worden, hier moet nog een integratie
	met fade bij zitten.
	$ledControl: gebruikt het aan/uit argument:
	- zet de strip uit met het command on, off
	of toggle. Integreer dit met fade om het uit
	te laten faden. Moet even nagedacht worden
	of er altijd een fade functie in moet zitten,
	ik ga het gewoon testen en kijken wat ik het
	meest gebruik.
	$fade: laat de strip aan/uit of naar een andere
	kleur faden:
	- Integreer dit met stripColor en ledControl,
	wanneer er een andere vooringestelde kleur wordt
	geselecteerd zoals blauw kan dit met een fade
	veranderen. Ook kan er voor het aan en uitgaan
	een fade worden toegepast.
	$pulse: laat de strip van de ene kleur naar de
	andere kleur pulsen:
	- Geef twee kleuren (dit kan dus ook zwart zijn)
	en een tijd mee hoe lang er tussen de pulse moet
	zitten, het moet ook mogelijk zijn om later de
	kleur en de tijd los van elkaar aan te passen.
	Bij de kleur wordt dan eerst de oude kleur
	gespecificeerd.

	Alle functienamen kunnen nog veranderd worden.
*/

// Include libraries.
#include <ESP8266WiFi.h>
//#include <DNSServer.h> I'm guessing wifi manager wanted this?
#include <ESP8266WebServer.h>
#include <FastLED.h>

// Add the file with wifi credentials. Excluded in the .gitignore.
#include "wifi.h"

#define NUM_LEDS 30
#define DATA_PIN D4

// Declare variables.
bool check = LOW; 
int crgb[3] = {0,255,255};
int orgb[3];
int nrgb[3];

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
	if (server.arg("power") == "on") {
		stripColor(crgb[0],crgb[1],crgb[2]);
		check = HIGH;
	} else if (server.arg("power") == "off") {
		stripColor(0,0,0);
		check = LOW;
	} else if (server.arg("power") == "toggle") {
		if (check == HIGH) {
			stripColor(0,0,0);
			check = LOW;
		} else {
			stripColor(crgb[0],crgb[1],crgb[2]);
			check = HIGH;
		}
	}
	server.send(200, "text/plain", "Processed.\n");
}


void setup() {
	// Setup basic stuff.
	Serial.begin(230400);

	// Wifi setup.
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.print(".");
        digitalWrite(D4,LOW);
        delay(250);
        digitalWrite(D4,HIGH);
    }
    Serial.println("Laat de strip heel snel heen en weer flitsen");
    Serial.println("Connected!");
    // Configure a static IP.
    WiFi.config(ip, gateway, subnet);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(100);

	server.on("/led", ledControl);
	server.begin();
	Serial.println("Server started.");
}


void loop() {
	// Call the server.
	server.handleClient();
}
