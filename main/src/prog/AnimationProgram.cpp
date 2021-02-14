#include "AnimationProgram.h"
#include "../util/Leds.h"
#include "data/animation/MarioGif.h"

static constexpr uint16_t FRAME_DELAY = 500;
static constexpr uint8_t FRAME_WIDTH = 12;
static constexpr uint8_t FRAME_HEIGHT = 12;

AnimationProgram::AnimationProgram(Animation animationIndex) :
		animationIndex(animationIndex), frameDelayTimer(FRAME_DELAY), currentFrame(0) {
	LOGF("Created animation program %d\n", animationIndex);
}

void AnimationProgram::loop() {
	if (!frameDelayTimer.isReady()) {
		return;
	}

	int maxFrames;
	switch (animationIndex) {
	case MARIO:
		Leds::drawImage(FRAME_WIDTH, FRAME_HEIGHT, mario_gif_array_array[currentFrame]);
		maxFrames = sizeof(mario_gif_array_array) / sizeof(mario_gif_array_array[0]);
		break;
	}

	if (++currentFrame >= maxFrames) {
		currentFrame = 0;
	}
}

AnimationProgram::~AnimationProgram() {
}

