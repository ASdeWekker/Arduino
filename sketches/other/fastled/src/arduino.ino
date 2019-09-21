#include "FastLED.h"

CRGB leds[30];

void setup() {
	FastLED.addLeds<NEOPIXEL, D4>(leds, 30);
	Serial.begin(230400);
}

void loop() {
	static uint8_t hue = 0;
	FastLED.showColor(CHSV(hue++, 255, 255));
	delay(100);
	Serial.println(hue);
}