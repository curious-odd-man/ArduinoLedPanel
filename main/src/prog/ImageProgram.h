#ifndef LIGHTPROGRAM_H_
#define LIGHTPROGRAM_H_

#include "colors/ColorProgram.h"

/**
 * The generic color program.
 * Any program that displays something on led panel should derive from this class
 *
 */
class ImageProgram {
public:

	ImageProgram() :
			colorProgram(nullptr) {

	}

	// Optionally, some programs may use ColorProgram to utilize
	void setColorProgram(ColorProgram *prog) {
		colorProgram = prog;
	}

	virtual ~ImageProgram() {
		if (colorProgram != nullptr) {
			delete colorProgram;
		}
	}

	virtual void loop() = 0;
protected:
	ColorProgram *colorProgram;
};

#endif
