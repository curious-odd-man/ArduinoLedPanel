#ifndef LEDS_LEDS_H_
#define LEDS_LEDS_H_

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

namespace Leds {

static constexpr int LEDS_WIDTH = 15;
static constexpr int LEDS_HEIGHT = 12;
static constexpr int NUM_LEDS = LEDS_HEIGHT * LEDS_WIDTH;

void initialize();

void decrementBrightness();
void incrementBrightness();

void fillLeds(const CRGB &color);
void printDigit3x5(uint8_t x, uint8_t y, uint8_t c, const CRGB &color);
void drawPixel(uint8_t x, uint8_t y, const CRGB &color);
void drawPixelAA(float x, float y, const CRGB &color);
void drawLetter(uint8_t letter, int16_t offset, const CRGB &color);
void drawImage(uint8_t imageWidth, uint8_t imageHeight, const uint16_t *frame);

void redraw();
void loop();

void clear();
void clear(const CRGB &color);
//void clearLine(uint8_t y);

constexpr uint8_t width() {
	return LEDS_WIDTH;
}

constexpr uint8_t height() {
	return LEDS_HEIGHT;
}

constexpr uint8_t maxX() {
	return LEDS_WIDTH - 1;
}

constexpr uint8_t maxY() {
	return LEDS_HEIGHT - 1;
}

}

inline CRGB randomColor() {
	return CRGB(random(256), random(256), random(256));
}

#endif /* LEDS_LEDS_H_ */
