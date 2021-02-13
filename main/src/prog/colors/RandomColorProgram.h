#ifndef SRC_PROG_COLORS_RANDOMCOLORPROGRAM_H_
#define SRC_PROG_COLORS_RANDOMCOLORPROGRAM_H_

#include "ColorProgram.h"
#include "../../util/common.h"

class RandomColorProgram: public ColorProgram {
public:
	RandomColorProgram() {
		LOG("RandomColorProgram is used");
	}

	CRGB getColor(uint8_t x, uint8_t y) override {
		(void) x;
		(void) y;
		return randomColor();
	}

	virtual ~RandomColorProgram() {

	}
};

#endif /* SRC_PROG_COLORS_RANDOMCOLORPROGRAM_H_ */
