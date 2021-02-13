#ifndef ROLLINGBALLPROGRAM_H_
#define ROLLINGBALLPROGRAM_H_

#include "ImageProgram.h"
#include "../util/Point2d.h"

class RollingBallProgram: public ImageProgram {
public:
	RollingBallProgram(uint8_t size);
	RollingBallProgram() :
			RollingBallProgram((uint8_t) random(0x1, 0x4)) {

	}

	virtual void loop() override;
	virtual ~RollingBallProgram();
private:
	Point2d<float> position;
	Point2d<float> movement;
	uint8_t size;
};
#endif /* ROLLINGBALLPROGRAM_H_ */
