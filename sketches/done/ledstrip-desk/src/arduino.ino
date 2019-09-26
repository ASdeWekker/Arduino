/*
	Ik wil dat de strip via led wordt aangeroepen.
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

/*
	Hue colors:
		Red:		0
		Orange:		32
		Yellow:		64
		Green:		96
		Aqua:		128
		Blue:		160
		Purple:		192
		Pink:		224
*/

/*
	Going to add a todo list.
	TODO:
		Thing 1.
*/

// Include libraries.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

// Add the file with wifi credentials. Excluded in the .gitignore.
#include "wifi.h"

#define NUM_LEDS 30
#define DATA_PIN D4
#define LED_TYPE WS2811
#define COLOR_ORDER BRG

// Declare variables.
bool check = true;
bool rainbowSet = false;
int rainbowSpeed = 10;
int brightnessInt = 255;

uint8_t ccolor = 128;
uint8_t ocolor;
uint8_t ncolor;
uint8_t hue = 0;

ESP8266WebServer server(80);

CRGB leds[NUM_LEDS];


/*
	Moved all the functions to their own functions.ino
*/


// The setup.
void setup() {
	Serial.begin(230400); // Turn on the serial connection.

	// Wifi setup.
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(50);
		Serial.print(".");
	}
	WiFi.config(ip, gateway, subnet); // Configure a static IP.

	// Some FastLED setup stuff.
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);

	// Add the routes and start the server.
	server.on("/power", power); server.on("/color", color); server.on("/rgb", rgb);
	server.on("/hsv", hsv); server.on("/rainbow", rainbow); server.on("/brightness", brightness);
	server.begin();
	Serial.println("Server started.");

	// Turn the strip on after powering the wemos on.
	stripColor(ccolor, true);
}


// The loop.
void loop() {
	server.handleClient(); // Call the server.

	if (rainbowSet) {
		FastLED.showColor(CHSV(hue++, 255, brightnessInt));
		delay(rainbowSpeed);
	} else {
		; // Do nothing.
	}
}
