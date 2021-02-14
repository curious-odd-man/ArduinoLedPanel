#include <Arduino.h>

#include "RunningTextProgram.h"
#include "../util/data/fonts.h"

static constexpr int SCROLL_TIMER = 50;

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
			// FIXME: There should be a prettier way to draw text. Should we have method drawText in a Leds as well?
			Leds::drawLetter((uint8_t) text[i], offset + j * (LETTER_WIDTH + SPACE), colorProgram == nullptr ? color : colorProgram->getColor(0, i));
			i++;
			j++;
		}
	}

	offset--;
	if (offset < -j * (LETTER_WIDTH + SPACE)) {
		offset = Leds::width() + 3;
	}
}

RunningTextProgram::~RunningTextProgram() {
}

