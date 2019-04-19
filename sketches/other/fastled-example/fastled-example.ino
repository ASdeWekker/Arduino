// Het is dus als volgt:
// Rood, Blauw, Groen.

#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN D4

int potrpin = D2;
int potgpin = D1;
int potbpin = A0;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(230400);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(30);
}

void loop() {
  int potr = analogRead(potrpin);
  int potg = analogRead(potgpin);
  int potb = analogRead(potbpin);

  int potrval = map(potr, 0, 1023, 0, 255);
  int potgval = map(potg, 0, 1023, 0, 255);
  int potbval = map(potb, 0, 1023, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(potrval, potbval, potgval);
    FastLED.show();
    Serial.print("Potr: "); Serial.print(potr); Serial.print(", Potrval: "); Serial.println(potrval);
    Serial.print("Potg: "); Serial.print(potg); Serial.print(", Potgval: "); Serial.println(potgval);
    Serial.print("Potb: "); Serial.print(potb); Serial.print(", Potbval: "); Serial.println(potbval);
    delayMicroseconds(1);
  }
}
