#ifndef SRC_PROG_COLORS_COLORPROGRAM_H_
#define SRC_PROG_COLORS_COLORPROGRAM_H_

#include <stdint.h>
#include "../../util/Leds.h"

class ColorProgram {
public:
	ColorProgram() = default;
	virtual CRGB getColor(uint8_t x, uint8_t y) = 0;
	virtual ~ColorProgram() = default;
};

ColorProgram* createRandomColorProgram();

#include "StaticColorProgram.h"
#include "RandomColorProgram.h"
#include "LerpColorProgram.h"

#endif /* SRC_PROG_COLORS_COLORPROGRAM_H_ */
