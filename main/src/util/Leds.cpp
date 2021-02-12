#include "Leds.h"
#include "math.h"
#include "common.h"

namespace Leds {

static constexpr int LED_PIN = 2;
static constexpr int CURRENT_LIMIT = 5000; // mA, 0 to turn off
static constexpr int BRIGHTNESS = 100;
static constexpr EOrder COLOR_ORDER = GRB;

static CRGB leds[NUM_LEDS];
static bool shouldRedraw = false;

void initialize() {
	FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(
			TypicalLEDStrip);

	FastLED.setBrightness(BRIGHTNESS);
	if (CURRENT_LIMIT > 0) {
		FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	}
	FastLED.clear();
	FastLED.show();
}

void fillLeds(const CRGB &color) {
	FastLED.showColor(color);
	redraw();
}

void setBrightness(uint8_t scale) {
	FastLED.setBrightness(scale);
}

void decrementBrightness() {
	FastLED.setBrightness(max(1, FastLED.getBrightness() - 1));
	redraw();
}

void incrementBrightness() {
	FastLED.setBrightness(min(255, FastLED.getBrightness() + 1));
	redraw();
}

void redraw() {
	shouldRedraw = true;
}

void loop() {
	if (shouldRedraw) {
		FastLED.show();
		shouldRedraw = false;
	}
}

//@formatter:off
// Probably these might be moved to PROGMEM, though now i have enough memory
static const uint8_t font3x5[][3] = {
  {0b01111, 0b10001, 0b11110},    // 0
  {0b01000, 0b11111, 0b00000},    // 1
  {0b10011, 0b10101, 0b01001},    // 2
  {0b10001, 0b10101, 0b11111},    // 3
  {0b11100, 0b00100, 0b11111},    // 4
  {0b11101, 0b10101, 0b10111},    // 5
  {0b01111, 0b10101, 0b10111},    // 6
  {0b10000, 0b10011, 0b11100},    // 7
  {0b11111, 0b10101, 0b11111},    // 8
  {0b11101, 0b10101, 0b11110},    // 9
};

static const uint8_t pixelIndexes[LEDS_HEIGHT][LEDS_WIDTH] = {
    {179,178,177,176,175,174,173,172,171,170,169,168,167,166,165},
    {150,151,152,153,154,155,156,157,158,159,160,161,162,163,164},
    {149,148,147,146,145,144,143,142,141,140,139,138,137,136,135},
    {120,121,122,123,124,125,126,127,128,129,130,131,132,133,134},
    {119,118,117,116,115,114,113,112,111,110,109,108,107,106,105},
    {90,91,92,93,94,95,96,97,98,99,100,101,102,103,104},
    {89,88,87,86,85,84,83,82,81,80,79,78,77,76,75},
    {60,61,62,63,64,65,66,67,68,69,70,71,72,73,74},
    {59,58,57,56,55,54,53,52,51,50,49,48,47,46,45},
    {30,31,32,33,34,35,36,37,38,39,40,41,42,43,44},
    {29,28,27,26,25,24,23,22,21,20,19,18,17,16,15},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}
};
//@formatter:oninline
static inline uint8_t getPixelIndex(uint8_t x, uint8_t y) {
	return pixelIndexes[y][x];
}

/**
 * Note, after calling this function set shouldRedraw = true; to actually light leds
 */
static void drawPixelIntern(uint8_t x, uint8_t y, const CRGB &color) {
	if (x > LEDS_WIDTH - 1 || y > LEDS_HEIGHT - 1) {
		LOGF("Failed to print pixel at x=%d y=%d\n", x, y);
		return;
	}

	leds[getPixelIndex(x, y)] = color;
}

static void drawPixelInternAA(float ix, float iy, const CRGB &color) {
	if (ix > LEDS_WIDTH - 1 || iy > LEDS_HEIGHT - 1) {
		LOGF("Failed to print pixel at x=%f y=%f\n", ix, iy);
		return;
	}

	//LOGF("Printing point at %f %f\n", ix, iy);

	for (int x = floor(ix); x <= ceil(ix); ++x) {
		for (int y = floor(iy); y <= ceil(iy); ++y) {
			float dx = ix - (float)x;
			float dy = iy - (float)y;
			float px = 1.0 - fabs(dx);
			float py = 1.0 - fabs(dy);
			float pp = px * py;
			int ledIndex = getPixelIndex(x, y);
			leds[ledIndex].setRGB(color.r * pp, color.g * pp, color.b * pp);
			//LOGF("x %d, y %d, px %f, py %f, pp %f\n", x, y, px, py, pp);
		}
	}
}

void drawPixelAA(float x, float y, const CRGB &color) {
	drawPixelInternAA(x, y, color);
	shouldRedraw = true;
}

/**
 * This should only be called externally, if needed.
 */
void drawPixel(uint8_t x, uint8_t y, const CRGB &color) {
	drawPixelIntern(x, y, color);
	shouldRedraw = true;
}

void printDigit3x5(uint8_t x, uint8_t y, uint8_t d, const CRGB &color) {
	if (d > 9) {
		return printDigit3x5(x, y, '0', color);
	}

	for (uint8_t xi = 0; xi < 3; ++xi) {
		uint8_t thisByte = font3x5[d][xi];
		for (uint8_t yi = 0; yi < 5; ++yi) {
			if (thisByte & (1 << yi)) {
				drawPixelIntern(x + xi, y + 4 - yi, color);
			}
		}
	}
	shouldRedraw = true;
}

void clear() {
	FastLED.clearData();
}

void clear(const CRGB &color) {
	fillLeds(color);
}

}

