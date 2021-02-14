#include "Leds.h"
#include "math.h"
#include "common.h"
#include "data/fonts.h"

namespace Leds {

static constexpr int LED_PIN = 2;
static constexpr int CURRENT_LIMIT = 400; // mA, 0 to turn off
static constexpr int BRIGHTNESS = 10;
static constexpr EOrder COLOR_ORDER = GRB;

static CRGB leds[NUM_LEDS];
static bool shouldRedraw = false;

void initialize() {
	FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

	FastLED.setBrightness(BRIGHTNESS);
	if (CURRENT_LIMIT > 0) {
		FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	}
	FastLED.clear();
	FastLED.show();
}

void fillLeds(const CRGB &color) {
	fill_n(leds, NUM_LEDS, color);
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

#include "data/ledindex.h"

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
			float dx = ix - (float) x;
			float dy = iy - (float) y;
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

#include "data/font3x5.h"
// TODO: This could also receive ColorProgram* and use it
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

#include "data/gammacorrection.h"

static uint32_t gammaCorrection(uint32_t color) {
	byte r = (color >> 16) & 0xFF;  // Extract the RR byte
	byte g = (color >> 8) & 0xFF;   // Extract the GG byte
	byte b = color & 0xFF;        // Extract the BB byte

	r = pgm_read_byte(&gammaR[r]);
	g = pgm_read_byte(&gammaG[g]);
	b = pgm_read_byte(&gammaB[b]);

	uint32_t newColor = ((long) (r & 0xff) << 16) + ((long) (g & 0xff) << 8) + ((long) b & 0xff);
	return newColor;
}

#include "data/expandColorCorrection.h"

static uint32_t expandColor(uint16_t color) {
	return ((uint32_t) pgm_read_byte(&gamma5[color >> 11]) << 16) | ((uint32_t) pgm_read_byte(&gamma6[(color >> 5) & 0x3F]) << 8) | pgm_read_byte(&gamma5[color & 0x1F]);
}

void drawImage(uint8_t imageWidth, uint8_t imageHeight, const uint16_t *frame) {
	int8_t offset_x = (Leds::width() - imageWidth) / 2;
	int8_t offset_y = (Leds::height() - imageHeight) / 2;
	for (byte i = 0; i < imageWidth; i++) {
		if (offset_x + i < 0 || offset_x + i > Leds::maxX()) {
			continue;
		}
		for (byte j = 0; j < imageHeight; j++) {
			if (offset_y + j < 0 || offset_y + j > Leds::maxY()) {
				continue;
			}
			CRGB color = gammaCorrection(expandColor((pgm_read_word(&(frame[(Leds::height() - j - 1) * Leds::width() + i])))));
			drawPixelIntern(offset_x + i, offset_y + j, color);
		}
	}
	redraw();
}

static uint8_t getLetterByte(uint8_t letter, uint8_t row) {
	letter = letter - '0' + 16;
	if (letter <= 90) {
		return pgm_read_byte(&(fontHEX[letter][row]));
	} else if (letter >= 112 && letter <= 159) {
		return pgm_read_byte(&(fontHEX[letter - 17][row]));
	} else if (letter >= 96 && letter <= 111) {
		return pgm_read_byte(&(fontHEX[letter + 47][row]));
	}
	return 0;
}

void drawLetter(uint8_t letter, int16_t offset, const CRGB &letterColor) {
	int8_t start_pos = 0;
	int8_t finish_pos = LETTER_WIDTH;
	int8_t letterHeight = min(LETTER_HEIGHT, Leds::height());
	int8_t offset_y = (Leds::height() - letterHeight) / 2;

	if (offset < -LETTER_WIDTH || offset > Leds::width()) {
		return;
	}

	if (offset < 0) {
		start_pos = -offset;
	}

	if (offset > (Leds::width() - LETTER_WIDTH)) {
		finish_pos = Leds::width() - offset;
	}

	for (uint8_t i = start_pos; i < finish_pos; i++) {
		int letterByte = getLetterByte(letter, i);
		for (uint8_t j = 0; j < letterHeight; j++) {
			if (letterByte & (1 << j)) {
				Leds::drawPixel(offset + i, offset_y + j, letterColor);
			}
		}
	}
}

}

