#ifndef SRC_PROG_COLORS_STATICCOLORPROGRAM_H_
#define SRC_PROG_COLORS_STATICCOLORPROGRAM_H_

#include "ColorProgram.h"
#include "../../util/common.h"

class StaticColorProgram: public ColorProgram {
public:
	StaticColorProgram() :
			color(randomColor()) {
		LOG("StaticColorProgram is used");
	}

	StaticColorProgram(const CRGB &color) :
			color(color) {
		LOG("StaticColorProgram is used");
	}

	CRGB getColor(uint8_t x, uint8_t y) override {
		(void) x;
		(void) y;
		return color;
	}

	virtual ~StaticColorProgram() = default;

private:
	CRGB color;
};

#endif /* SRC_PROG_COLORS_STATICCOLORPROGRAM_H_ */
