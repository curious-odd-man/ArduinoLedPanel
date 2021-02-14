#ifndef SRC_PROG_ANIMATIONPROGRAM_H_
#define SRC_PROG_ANIMATIONPROGRAM_H_

#include "ImageProgram.h"
#include "../util/TimerMs.h"

enum Animation : uint8_t {
	MARIO,
};

class AnimationProgram: public ImageProgram {
public:
	AnimationProgram(Animation animationIndex);
	virtual void loop() override;
	virtual ~AnimationProgram();
private:
	Animation animationIndex;
	TimerMs frameDelayTimer;
	uint8_t currentFrame;
};

#endif /* SRC_PROG_ANIMATIONPROGRAM_H_ */
