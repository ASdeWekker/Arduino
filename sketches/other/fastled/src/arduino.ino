#include "FastLED.h"

#define NUM_LEDS 30
#define DATA_PIN D4
#define LED_TYPE WS2811
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

const int snel = 10;
const int normaal = 50;
const int langzaam = 100;
const int nauwelijks = 200;
const int ultraLangzaam = 1000;

bool removeOrAdd = true;

static uint8_t gHue = 0;
// static uint8_t led = 0;
// static uint8_t rainbowPos = 0;

void setup() {
	Serial.begin(230400);

	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);
	FastLED.show(CRGB::Black);
	delay(ultraLangzaam);
}

void juggle() {
	// eight colored dots, weaving in and out of sync with each other
	fadeToBlackBy( leds, NUM_LEDS, 20);
	byte dotgHue = 0;
	for (int i = 0; i < 8; i++) {
		leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dotgHue, 200, 255);
		dotgHue += 32;
	}	
}

void bpm() {
	// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
	uint8_t BeatsPerMinute = 150;
	CRGBPalette16 palette = PartyColors_p;
	uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
	for (int i = 0; i < NUM_LEDS; i++) { //9948
		leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
	}
}

void sinelon() {
	// a colored dot sweeping back and forth, with fading trails
	fadeToBlackBy(leds, NUM_LEDS, 20);
	int pos = beatsin16(13, 0, NUM_LEDS-1);
	leds[pos] += CHSV(gHue++, 255, 255);
}

void confetti() {
	// random colored speckles that blink in and fade smoothly
	fadeToBlackBy(leds, NUM_LEDS, 10);
	int pos = random16(NUM_LEDS);
	leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void rainbow() {
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88(87, 220, 250);
	uint8_t brightdepth = beatsin88(341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis ;
	sLastMillis  = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400, 5,9);
	uint16_t brightnesstheta16 = sPseudotime;

	for(uint16_t i = 0; i < NUM_LEDS; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16  += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV(hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS-1) - pixelnumber;

		nblend(leds[pixelnumber], newcolor, 64);
	}
}

void loop() {
	// fill_rainbow(leds, NUM_LEDS, gHue, rainbowPos);
	// juggle();
	// bpm();
	// sinelon();
	// confetti();
	rainbow();
	FastLED.show();
	delay(snel);
}
