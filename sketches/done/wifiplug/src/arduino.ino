
/*
	initial commit.
*/

// Include libraries.
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// And the wifi credentials.
#include "wifi.h"


// Declare some variables.
bool check = LOW;
int relay = D4;

// Start the webserver.
ESP8266WebServer server(80);

// A function for controlling the relay.
void power() {
	if (server.arg("power") == "on") {
		digitalWrite(relay, HIGH);
		check = HIGH;
	} else if (server.arg("power") == "off") {
		digitalWrite(relay, LOW);
		check = LOW;
	} else if (server.arg("power") == "toggle") {
		if (check == HIGH) {
			digitalWrite(relay, LOW);
			check = LOW;
		} else if (check == LOW) {
			digitalWrite(relay, HIGH);
			check = HIGH;
		}
	}
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
        delay(250);
        Serial.print(".");
    }
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
