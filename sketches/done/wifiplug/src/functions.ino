// This is where all the functions will live.

// A function for controlling the RELAY_PIN.
void power() {
	if (server.arg("power") == "on") {
		digitalWrite(RELAY_PIN, HIGH);
		powerCheck = true;
	} else if (server.arg("power") == "off") {
		digitalWrite(RELAY_PIN, LOW);
		powerCheck = false;
	} else if (server.arg("power") == "toggle") {
		if (powerCheck == true) {
			digitalWrite(RELAY_PIN, LOW);
			powerCheck = false;
		} else if (powerCheck == false) {
			digitalWrite(RELAY_PIN, HIGH);
			powerCheck = true;
		}
	}
	server.send(200, "text/plain", "Processed.\n");
}
