#include "FastLED.h"

CRGB leds[30];

const int snel = 10;
const int normaal = 50;
const int langzaam = 100;
const int nauwelijks = 200;
const int ultra_langzaam = 1000;

void setup() {
	FastLED.addLeds<NEOPIXEL, D4>(leds, 30);
}

void loop() {
	static uint8_t hue = 0;
	FastLED.showColor(CHSV(hue++, 255, 255));
	delay(ultra_langzaam);
}
