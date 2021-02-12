#ifndef SRC_PROG_COLORS_COLORPROGRAM_H_
#define SRC_PROG_COLORS_COLORPROGRAM_H_

#include <stdint.h>
#include <FastLED.h>

class ColorProgram {
public:
	ColorProgram() = default;
	virtual CRGB getColor(uint8_t x, uint8_t y) = delete;
	virtual ~ColorProgram() = default;
};

#endif /* SRC_PROG_COLORS_COLORPROGRAM_H_ */
