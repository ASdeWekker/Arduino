// This is where all the functions will be.

// A function to set the proper CORS header.
void serverSend(String message) {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	server.send(200, "text/json", message);
}

// Display a message when root is accessed.
void root() { serverSend("You're not supposed to be here"); }

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
	if (powerCheck) { serverSend("{status: on}"); }
	else { serverSend("{status: off}"); }
}

void status() {
	if (powerCheck) { serverSend("{status: on}"); }
	else { serverSend("{status: off}"); }
}