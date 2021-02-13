#include "LerpColorProgram.h"
#include "../../util/common.h"

constexpr uint8_t LERP_STEPS = 10;

LerpColorProgram::LerpColorProgram() :
		colors( { randomColor(), randomColor(), randomColor(), randomColor() }), fromColor(colors.begin()), toColor(getNext(fromColor)), currentStep(0) {
	LOG("LERP ColorProgram is used with:");
	for (auto &clr : colors) {
		LOGF("\tColor 0x%02x%02x%02x: \n", clr.r, clr.g, clr.b);
	}
}

CRGB LerpColorProgram::getColor(uint8_t x, uint8_t y) {
	(void) x;
	(void) y;

	if (currentStep >= LERP_STEPS) {
		fromColor = getNext(fromColor);
		toColor = getNext(toColor);
		currentStep = 0;
	}

	CRGB ret = fromColor->lerp8(*toColor, (float) currentStep / LERP_STEPS);
	++currentStep;
	return ret;
}

vector<CRGB>::iterator LerpColorProgram::getNext(vector<CRGB>::iterator it) {
	if (it == colors.end()) {
		return colors.begin();
	} else {
		return ++it;
	}
}

LerpColorProgram::~LerpColorProgram() {

}

