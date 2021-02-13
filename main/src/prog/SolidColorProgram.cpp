#include "SolidColorProgram.h"

#include "../util/common.h"

SolidColorProgram::SolidColorProgram(const CRGB &color, uint8_t changeTimeSeconds) :
		color(color), changeTimer(changeTimeSeconds, false) {
	LOG("Solid Color Program created");
}

void SolidColorProgram::loop() {
	if (!changeTimer.isReady()) {
		return;
	}

	Leds::fillLeds(colorProgram == nullptr ? color : colorProgram->getColor(0, 0));
}

SolidColorProgram::~SolidColorProgram() {
}

