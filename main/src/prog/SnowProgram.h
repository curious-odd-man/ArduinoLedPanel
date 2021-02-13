#ifndef SNOWPROGRAM_H_
#define SNOWPROGRAM_H_

#include "ImageProgram.h"
#include <stdint.h>
#include <queue>

#include "../util/Leds.h"

struct Snowflake {
	uint8_t x;
	uint8_t y;
	unsigned long speed;
	unsigned long nextAction;
	CRGB color;

	//Create new snowflake
	Snowflake(uint8_t x, unsigned long speed) :
			x(x), y(0), speed(speed), nextAction(millis()), color(randomColor()) {

	}

	// Copy
	Snowflake(const Snowflake &sf) :
			x(sf.x), y(sf.y), speed(sf.speed), nextAction(sf.nextAction), color(sf.color) {

	}

	Snowflake(uint8_t x, uint8_t y, unsigned long speed, unsigned long nextAction, const CRGB &color) :
			x(x), y(y), speed(speed), nextAction(nextAction), color(color) {

	}
};

class SnowflakeCmp {
public:
	bool operator()(const Snowflake *lhs, const Snowflake *rhs) const;
};

class SnowProgram: public ImageProgram {
public:
	SnowProgram();
	virtual void loop() override;
	virtual ~SnowProgram();

private:
	unsigned long nextSnowflakeAt;
	std::priority_queue<Snowflake*, std::vector<Snowflake*>, SnowflakeCmp> snowflakes;

	void drawSnowflake(Snowflake *sf);
};

#endif /* SNOWPROGRAM_H_ */
