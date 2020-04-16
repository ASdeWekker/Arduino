
/*
	Test project for use with MQTT.
*/

// Include libraries.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// And the wifi configuration file.
#include "wifi.h"

// Some vars.
const int led = D4;
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
	server.on("/", root);
	server.begin();
	Serial.println("Server started.");
}


// The loop.
void loop() {
	// Call the server.
	server.handleClient();
}

void root() {
	// Do something.
}