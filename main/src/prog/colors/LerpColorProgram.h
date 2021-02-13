#ifndef SRC_PROG_COLORS_LERPCOLORPROGRAM_H_
#define SRC_PROG_COLORS_LERPCOLORPROGRAM_H_

#include "ColorProgram.h"
#include <vector>

using namespace std;

class LerpColorProgram: public ColorProgram {
public:
	LerpColorProgram();
	CRGB getColor(uint8_t x, uint8_t y) override;
	virtual ~LerpColorProgram();

private:
	vector<CRGB> colors;
	vector<CRGB>::iterator fromColor;
	vector<CRGB>::iterator toColor;
	uint8_t currentStep;

	vector<CRGB>::iterator getNext(vector<CRGB>::iterator it);
};

#endif /* SRC_PROG_COLORS_LERPCOLORPROGRAM_H_ */
