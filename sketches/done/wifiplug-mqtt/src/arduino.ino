
/*
	Test project for use with MQTT.
*/

// Include libraries.
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// And the wifi configuration file.
#include "wifi.h"

WiFiClient espClient;
PubSubClient client(espClient);

int status = WL_IDLE_STATUS;
bool ledState = false;
long tbm = 1000 * 20; // time between messages.
long lastMsg;

void setup_wifi() {
	delay(10);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("connected");
}

void callback(char* topic, byte* payload, int length) {
	Serial.print("sub msg: ");
	for (int i = 0; i < length; i++) { Serial.print((char)payload[i]); }
	Serial.println();
	if ((char)payload[0] == '1') {
		digitalWrite(LED_BUILTIN, LOW);
		ledState = HIGH;
	} else {
		digitalWrite(LED_BUILTIN, HIGH);
		ledState = LOW;
	}
}

void reconnect() {
	while (!client.connected()) {
		if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
			Serial.println("Connected");
			client.publish(topic, ("connected " + clientId).c_str(), true);
			String subscription = "wemos/" + clientId + "/in";
			client.subscribe(subscription.c_str());
			Serial.println("sub: " + subscription);
		} else {
			Serial.println("rc=" + client.state());
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	setup_wifi();
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}

void loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	long now = millis();
	if (now - lastMsg > tbm) {
		lastMsg = now;
		String payload; payload += "{\"status\":\""; payload += ledState; payload += "\"}";
		String pubTopic = "wemos/" + clientId + "/out";
		Serial.println("pub: " + pubTopic);
		Serial.println("pub msg: " + payload);
		client.publish((char*)pubTopic.c_str(), (char*)payload.c_str(), true);
	}
}