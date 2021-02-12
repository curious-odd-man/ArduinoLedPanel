#include "TimeProgram.h"
#include "../util/NtpTime.h"
#include "../util/common.h"
#include "../util/Leds.h"

static CRGB color = CRGB::Cyan;
static CRGB black = CRGB::Black;
//static constexpr CRGB red = CRGB::Red;
static constexpr uint8_t DIGITS_POS_X[] = { 0, 4, 8, 12 };
static constexpr uint8_t DIGITS_POS_Y = 3;
static constexpr uint8_t SECONDS_DOT_X = 7;
static constexpr uint8_t SECONDS_DOT_Y = 8;

//static constexpr uint8_t INITIALIZED_X = 0;
//static constexpr uint8_t INITIALIZED_Y = 0;

TimeProgram::TimeProgram() :
        secondsTimer(1000, false), minutesTimer(60000, false) {
}

void TimeProgram::loop() {
    if (secondsTimer.isReady()) {
        if (drawDot) {
            Leds::drawPixel(SECONDS_DOT_X, SECONDS_DOT_Y, color);
        } else {
            Leds::drawPixel(SECONDS_DOT_X, SECONDS_DOT_Y, black);
        }

        drawDot = !drawDot;

        if (minutesTimer.isReady() || !isInitialized) {
            tmElements_t tm;
            time_t now = NtpTime::nowToStruct(tm);
            if (now == 0) {
                LOG("Time not initialized...");
            } else {
                Leds::clear();
                uint8_t digits[] = { tm.Hour / 10, tm.Hour % 10, tm.Minute / 10, tm.Minute % 10 };
                LOGF("Current time: %d%d:%d%d\n", digits[0], digits[1], digits[2], digits[3]);
                for (uint8_t i = 0; i < sizeof(digits); ++i) {
                    Leds::printDigit3x5(DIGITS_POS_X[i], DIGITS_POS_Y, digits[i], color);
                }
                isInitialized = true;
            }
        }
    }
}

TimeProgram::~TimeProgram() {

}

