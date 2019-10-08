// This is where all the functions will live.

// A function for controlling the relay.
void power() {
	if (server.arg("power") == "on") {
		digitalWrite(relay, HIGH);
		powerCheck = true;
	} else if (server.arg("power") == "off") {
		digitalWrite(relay, LOW);
		powerCheck = false;
	} else if (server.arg("power") == "toggle") {
		if (powerCheck == true) {
			digitalWrite(relay, LOW);
			powerCheck = false;
		} else if (powerCheck == false) {
			digitalWrite(relay, HIGH);
			powerCheck = true;
		}
	}
	server.send(200, "text/plain", "Processed.\n");
}
