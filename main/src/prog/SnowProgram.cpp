#include "SnowProgram.h"

#include "../util/TimerMs.h"
#include "../util/common.h"

static CRGB BLACK_COLOR = CRGB::Black;
static constexpr int MAX_SNOWFLAKES = 30;
static constexpr int MIN_SNOWFLAKE_RESPAWN_TIME = 10;
static constexpr int MAX_SNOWFLAKE_RESPAWN_TIME = 200;
static constexpr int MIN_SNOWFLAKE_SPEED = 100;
static constexpr int MAX_SNOWFLAKE_SPEED = 200;
static constexpr int MAX_SNOWFLAKES_MOVE_PER_LOOP = 10;

bool SnowflakeCmp::operator()(const Snowflake *lhs, const Snowflake *rhs) const {
	return lhs->nextAction > rhs->nextAction;
}

SnowProgram::SnowProgram() :
		nextSnowflakeAt(0) {
	LOG("Snow program created");
}

void SnowProgram::loop() {
	unsigned long now = millis();

	if (nextSnowflakeAt < now && snowflakes.size() < MAX_SNOWFLAKES) {
		nextSnowflakeAt = now + random(MIN_SNOWFLAKE_RESPAWN_TIME, MAX_SNOWFLAKE_RESPAWN_TIME);
		uint8_t snowflakeX = random(Leds::width());
		drawSnowflake(new Snowflake(snowflakeX, 0, random(MIN_SNOWFLAKE_SPEED, MAX_SNOWFLAKE_SPEED), millis(), colorProgram == nullptr ? randomColor() : colorProgram->getColor(snowflakeX, 0)));
	}

	if (!snowflakes.empty()) {
		for (int i = 0; i < MAX_SNOWFLAKES_MOVE_PER_LOOP; ++i) {
			Snowflake *sf = snowflakes.top();
			if (now > sf->nextAction) {
				snowflakes.pop();
				Leds::drawPixel(sf->x, sf->y, BLACK_COLOR);
				if (sf->y < Leds::maxY()) {
					++sf->y;
					sf->nextAction = now + sf->speed;
					drawSnowflake(sf);
				} else {
					delete sf;
				}
			} else {
				break;
			}
		}
	}
}

void SnowProgram::drawSnowflake(Snowflake *sf) {
	snowflakes.push(sf);
	Leds::drawPixel(sf->x, sf->y, sf->color);
}

SnowProgram::~SnowProgram() {
}

