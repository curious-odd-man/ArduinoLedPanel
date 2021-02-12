#ifndef SRC_PROG_COLORS_STATICCOLORPROGRAM_H_
#define SRC_PROG_COLORS_STATICCOLORPROGRAM_H_

#include "ColorProgram.h"

class StaticColorProgram: public ColorProgram {
public:
	StaticColorProgram(const CRGB &color) :
			color(color) {
	}

	CRGB getColor(uint8_t x, uint8_t y) override {
		return color;
	}

	virtual ~StaticColorProgram() = default;

private:
	CRGB color;
};

#endif /* SRC_PROG_COLORS_STATICCOLORPROGRAM_H_ */
