#ifndef LEDS_SOLIDCOLORPROGRAM_H_
#define LEDS_SOLIDCOLORPROGRAM_H_

#include "ImageProgram.h"
#include "../util/Leds.h"
#include "../util/TimerMs.h"

class SolidColorProgram: public ImageProgram {
private:
	CRGB color;
	TimerMs changeTimer;
public:
	SolidColorProgram(const CRGB &color, uint8_t changeTimeMs);
	SolidColorProgram() :
			SolidColorProgram(randomColor(), random(200, 500)) {

	}
	virtual void loop() override;
	virtual ~SolidColorProgram();
};

#endif /* LEDS_SOLIDCOLORPROGRAM_H_ */
