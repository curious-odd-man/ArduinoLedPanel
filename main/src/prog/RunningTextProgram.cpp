#include <Arduino.h>

#include "RunningTextProgram.h"
#include "../util/fonts.h"

static constexpr int SCROLL_TIMER = 50;
static constexpr uint8_t LETTER_WIDTH = 5;
static constexpr uint8_t LETTER_HEIGHT = 8;
static constexpr int SPACE = 1;

RunningTextProgram::RunningTextProgram(const char *text, const CRGB &color) :
		offset(Leds::width()), scrollTimer(SCROLL_TIMER), text(text), color(color) {
	LOGF("Running text program created with text: '%s'\n", text);
}

void RunningTextProgram::loop() {
	if (!scrollTimer.isReady()) {
		return;
	}

	Leds::clear();
	uint8_t i = 0;
	uint8_t j = 0;

	while (text[i] != '\0') {
		if ((uint8_t) text[i] > 191) { // skip first byte of UTF-8 encoded letter
			i++;
		} else {
			// FIXME: Each letter should have it's own color.
			drawLetter(text[i], offset + j * (LETTER_WIDTH + SPACE), colorProgram == nullptr ? color : colorProgram->getColor(0, i));
			i++;
			j++;
		}
	}

	offset--;
	if (offset < -j * (LETTER_WIDTH + SPACE)) {
		offset = Leds::width() + 3;
	}
}

void RunningTextProgram::drawLetter(uint8_t letter, int16_t offset, const CRGB &letterColor) {
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

uint8_t RunningTextProgram::getLetterByte(uint8_t letter, uint8_t row) {
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

RunningTextProgram::~RunningTextProgram() {
}

