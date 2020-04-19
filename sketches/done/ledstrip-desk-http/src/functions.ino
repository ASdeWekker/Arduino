// This is where all the functions will reside.

// A function to set the proper CORS header.
void serverSend(String message) {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	server.send(200, "text/json", message);
}

// Display a message when root is accessed.
void root() {
	serverSend("{\"message\": \"You're not supposed to be here\"}");
}

// A function for changing the ledstrip's color.
void stripColor(int color, bool power) {
	if (color == 1) { // When 1 is chosen the strip turns white.
		FastLED.showColor(CHSV(color, 0, brightnessVal));
	} else { // Otherwise do the normal thing.
		if (power == true) {
			FastLED.showColor(CHSV(color, 255, brightnessVal));
		} else if (power == false) {
			FastLED.show(CRGB::Black);
		}
	}
}

// A function for turning the ledstrip on or off.
void power() {
	// Checks which argument has been passed and turns the strip on or off.
	if (server.arg("power") == "on") {
		if (rainbowWasOn) {
			rainbowCheck = true;
		} else {
			stripColor(ccolor, true);
		}
		check = true;
		wakeUpCheck = false;
		fadeCheck = false;
		rainbowWasOn = false;
	} else if (server.arg("power") == "off") {
		if (rainbowCheck) {
			rainbowWasOn = true;
		}
		stripColor(ccolor, false);
		check = false;
		wakeUpCheck = false;
		rainbowCheck = false;
		fadeCheck = false;
	} else if (server.arg("power") == "toggle") {
		if (check == true) {
			if (rainbowCheck) {
				rainbowWasOn = true;
			}
			stripColor(ccolor, false);
			check = false;
			rainbowCheck = false;
			wakeUpCheck = false;
			fadeCheck = false;
		} else {
			if (rainbowWasOn) {
				rainbowCheck = true;
			} else {
				stripColor(ccolor, true);
			}
			check = true;
			wakeUpCheck = false;
			fadeCheck = false;
			rainbowWasOn = false;
		}
	}

	// Send a message back to the client.
	if (rainbowCheck) {
		serverSend("{\"message\": \"The power state has been altered.\", \"status\": \"on-r\"}");
	} else if (check) {
		serverSend("{\"message\": \"The power state has been altered.\", \"status\": \"on\"}");
	} else {
		serverSend("{\"message\": \"The power state has been altered.\", \"status\": \"off\"}");
	}
}

// A function for choosing a preprogrammed color.
void color() {
	// Check which color has been passed and act accordingly.
	if (server.arg("color") == "red") {
		ccolor = 0;
	} else if (server.arg("color") == "orange") {
		ccolor = 32;
	} else if (server.arg("color") == "yellow") {
		ccolor = 64;
	} else if (server.arg("color") == "green") {
		ccolor = 96;
	} else if (server.arg("color") == "aqua") {
		ccolor = 128;
	} else if (server.arg("color") == "blue") {
		ccolor = 160;
	} else if (server.arg("color") == "purple") {
		ccolor = 192;
	} else if (server.arg("color") == "pink") {
		ccolor = 224;
	} else if (server.arg("color") == "white") {
		ccolor = 1; // This isn't the true white value but stripColor() will check for it.
	}

	check = true;
	rainbowCheck = false;
	wakeUpCheck = false;

	// Set the color and send the processed message.
	stripColor(ccolor, true);
	serverSend("{\"message\": \"Changed the color\", \"status\": \"on\", \"color\": \"" + server.arg("color") + "\"}");
}

// A function to change the color via an rgb value.
void rgb() {
	// Going to make a function which takes an rgb value and converts it to an hsv value.

	// Send a message back to the client.
	serverSend("{\"message\": \"This function is not yet implemented.\"}");
}

// A function to change the color via an hsv value.
void hsv() {
	// This function takes an int and puts it into ccolor.
	ccolor = server.arg("hsv").toInt();
	stripColor(ccolor, true);
	check = true;
	rainbowCheck = false;
	wakeUpCheck = false;
	fadeCheck = false;

	// Send a message back to the client.
	serverSend("{\"message\": \"Processed the hsv color.\"}");
}

// A function to emit a rainbow at a certain speed.
void rainbow() {
	rainbowSpeed = server.arg("speed").toInt();
	rainbowCheck = true;
	check = true;
	wakeUpCheck = false;
	fadeCheck = false;
	rainbowWasOn = false;

	// Send a message back to the client.
	serverSend("{\"message\": \"Turned on the rainbow.\", \"status\": \"on-r\"}");
}

// A function to change the brightness.
void brightness() {
	brightnessVal = server.arg("brightness").toInt();
	stripColor(ccolor, true);

	// Send a message back to the client.
	serverSend("{\"message\": \"Changed the brightness.\"}");
}

// A function to wake up nicely in the morning.
void wakeUp() {
	// Set the saturation back to 255.
	saturation = 255;
	
	check = true;
	rainbowCheck = false;
	wakeUpCheck = true;
	fadeCheck = false;
	serverSend("{\"message\": \"Turned on the wake up function.\", \"status\": \"on-w\"}");
}

// A function to fade a color in and out.
void fade() {
	fadeDelay = server.arg("delay").toInt();
	// fadeDelay needs a value of 1 or greater or else it will turn off.
	if (fadeDelay != 0) {
		fadeCheck = true;
		serverSend("{\"message\": \"Turned on fade.\", \"status\": \"on-f\"}");
	} else {
		fadeCheck = false;
		serverSend("{\"message\": \"Turned off fade.\"}");
	}
	
	check = true;
	wakeUpCheck = false;
	rainbowCheck = false;
}

// A function to send back what happening right now.
void status() {
	if (rainbowCheck && check) {
		serverSend("{\"status\": \"on-r\"}");
	} else if (check) {
		serverSend("{\"status\": \"on\"}");
	} else {
		serverSend("{\"status\": \"off\"}");
	}
}
