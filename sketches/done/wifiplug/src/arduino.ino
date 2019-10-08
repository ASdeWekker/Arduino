
/*
	This is for the multiple wifi connected plugs I'll be having around my home.
	First plug is for the amplifier.
*/

// Include libraries.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// And the wifi configuration file.
#include "wifi.h"


// Declare the relay pin.
#define RELAY_PIN D3

// Declare some variables.
bool powerCheck = false;
int timeInSeconds = 0;

// Start the webserver.
ESP8266WebServer server(80);


// The setup.
void setup() {
	// Setup basic stuff.
	Serial.begin(230400);

	// Wifi setup.
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		timeInSeconds++;
		Serial.print(timeInSeconds);
		Serial.print(" ");
	}
	Serial.println("");
	Serial.print("Seconds untill connection: ");
	Serial.println(timeInSeconds);
	
	Serial.println("");
	Serial.println("Connected!");
	// Configure a static IP.
	WiFi.config(ip, gateway, subnet);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	// Add the routes and start the server.
	server.on("/power", power);
	server.begin();
	Serial.println("Server started.");
}


// The loop.
void loop() {
	// Call the server.
	server.handleClient();
}
