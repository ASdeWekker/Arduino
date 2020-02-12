// Display a message when root is accessed.
void root() {
	serverSend("You're not supposed to be here");
}

// A function to set the proper CORS header.
void serverSend(String message) {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	server.send(200, "text/plain", message);
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
	serverSend("Processed.\n");
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
	serverSend("Set the color: " + server.arg("color") + ".\n");
}


// A function to change the color via an rgb value.
void rgb() {
	// Going to make a function which takes an rgb value and converts it to an hsv value.

	// Send a message back to the client.
	serverSend("This function is not yet implemented.\n");
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
	serverSend("Processed the hsv color.\n");
}


// A function to emit a rainbow at a certain speed.
void rainbow() {
	rainbowSpeed = server.arg("speed").toInt();
	rainbowCheck = true;
	check = true;
	wakeUpCheck = false;
	fadeCheck = false;

	// Send a message back to the client.
	serverSend("Turned on the rainbow.\n");
}


// A function to change the brightness.
void brightness() {
	brightnessVal = server.arg("brightness").toInt();
	stripColor(ccolor, true);

	// Send a message back to the client.
	serverSend("Changed brightness.\n");
}

// A function to wake up nicely in the morning.
void wakeUp() {
	// Set the saturation back to 255.
	saturation = 255;
	
	check = true;
	rainbowCheck = false;
	wakeUpCheck = true;
	fadeCheck = false;
	serverSend("Wake up.\n");
}

// A function to fade a color in and out.
void fade() {
	fadeDelay = server.arg("delay").toInt();
	
	if (fadeDelay != 0) {
		fadeCheck = true;
		serverSend("Turned on fade.\n");
	} else {
		fadeCheck = false;
		serverSend("Turned off fade.\n");
	}
	
	check = true;
	wakeUpCheck = false;
	rainbowCheck = false;
}