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
bool check = LOW; 
int crgb[3] = {0,255,255};
int orgb[3];
int nrgb[3];

uint8_t ccolor = 128;
uint8_t ocolor;
uint8_t ncolor;

ESP8266WebServer server(80);

CRGB leds[NUM_LEDS];

// Function for changing the ledstrip's color.
void stripColor(int color, bool power) {
	if (power == HIGH) {
		FastLED.showColor(CHSV(color, 255, 255));
	} else if (power == LOW) {
		FastLED.showColor(CHSV(color, 255, 0));
	}
}

// A function for turning the ledstrip on or off.
void power() {
	// Checks which argument has been passed and turns the strip on or off.
	if (server.arg("power") == "on") {
		stripColor(ccolor,HIGH);
		check = HIGH;
	} else if (server.arg("power") == "off") {
		stripColor(ccolor,LOW);
		check = LOW;
	} else if (server.arg("power") == "toggle") {
		if (check == HIGH) {
			stripColor(ccolor,LOW);
			check = LOW;
		} else {
			stripColor(ccolor,HIGH);
			check = HIGH;
		}
	}
	server.send(200, "text/plain", "Processed.\n");
}

// A function for choosing a preprogrammed color.
void color() {
	// Check which color has been passed and act accordingly.
	if (server.arg("color") == "red") {
		ccolor = 0;
		check = HIGH;
	} else if (server.arg("color") == "orange") {
		ccolor = 32;
		check = HIGH;
	} else if (server.arg("color") == "yellow") {
		ccolor = 64;
		check = HIGH;
	} else if (server.arg("color") == "green") {
		ccolor = 96;
		check = HIGH;
	} else if (server.arg("color") == "aqua") {
		ccolor = 128;
		check = HIGH;
	} else if (server.arg("color") == "blue") {
		ccolor = 160;
		check = HIGH;
	} else if (server.arg("color") == "purple") {
		ccolor = 192;
		check = HIGH;
	} else if (server.arg("color") == "pink") {
		ccolor = 224;
		check = HIGH;
	}
	// A switch case seemed better than if statements, only it isn't working yet.
	// static char arg = server.arg("color");
	// switch (arg) {
	// 	case "red":
	// 		ccolor = 0;
	// 	case "orange":
	// 		ccolor = 32;
	// 	case "yellow":
	// 		ccolor = 64;
	// 	case "green":
	// 		ccolor = 96;
	// 	case "aqua":
	// 		ccolor = 128;
	// 	case "blue":
	// 		ccolor = 160;
	// 	case "purple":
	// 		ccolor = 192;
	// 	case "pink":
	// 		ccolor = 224;
	// }

	// Set the color and send the processed message.
	stripColor(ccolor,HIGH);
	server.send(200, "text/plain", "Processed.\n");
}

// A function for entering an rgb value.
void rgb() {
	// Still need to edit this to send back a message saying it isn't yet supported.
	// Going to make a function which takes an rgb value and converts it to an hsv value.
	String rgb = String(server.arg("rgb"));
	Serial.print("String: ");
	Serial.println(rgb);
	Serial.print("Normaal: ");
	Serial.println(server.arg("rgb"));
	server.send(200, "text/plain", "Processed.\n");
}

// A function to emit a rainbow at a certain speed.
void rainbow() {
	// Not working yet, may need to put it directly in void loop?
	static uint8_t hue = 0;
	// static String speedString = server.arg("speed");
	// static int speed = server.arg("speed").toInt();
	FastLED.showColor(CHSV(hue++, 255, 255));
	delay(50);
	server.send(200, "text/plain", "Processed.\n");
}


// The setup.
void setup() {
	// Setup basic stuff.
	Serial.begin(230400);

	// Wifi setup.
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(50);
		Serial.print(".");
		FastLED.showColor(CHSV(0,0,255));
		delay(50);
		FastLED.showColor(CHSV(0,0,0));
	}
	Serial.println("Connected!");
	// Configure a static IP.
	WiFi.config(ip, gateway, subnet);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	// Some FastLED setup stuff.
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(100);

	// Add the routes and start the server.
	server.on("/power", power);
	server.on("/color", color);
	server.on("/rgb", rgb);
	server.on("/rainbow", rainbow);
	server.begin();
	Serial.println("Server started.");
}


// The loop.
void loop() {
	// Call the server.
	server.handleClient();
}
