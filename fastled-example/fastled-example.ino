/*#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN D4

CRGB led[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
*/

#include "FastLED.h"
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
void setup() { FastLED.addLeds<NEOPIXEL, D4>(leds, NUM_LEDS); }
void loop() {
  leds[0] = CRGB::White; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
}
