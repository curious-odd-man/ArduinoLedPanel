#ifndef RANDOMCOLORPROGRAM_H_
#define RANDOMCOLORPROGRAM_H_

#include "ImageProgram.h"
#include <set>

#include "../util/TimerMs.h"
#include "../util/Leds.h"

class Fader {
public:
    CRGB color;
    uint8_t x;
    uint8_t y;

    // This is required for set
    Fader() :
            color(), x(0), y(0) {

    }

    Fader(CRGB &&color, uint8_t x, uint8_t y) :
            color(color), x(x), y(y) {

    }

    bool operator()(const Fader *lhs, const Fader *rhs) const {
        return lhs->x < rhs->x || (lhs->x == rhs->x && lhs->y < rhs->y);
    }

    bool is_black() const {
        if (color.r == 0 && color.g == 0 && color.b == 0) {
            return true;
        }

        return false;
    }
};

class FadingStarsProgram: public ImageProgram {
public:
    FadingStarsProgram();
    virtual void loop() override;
    virtual ~FadingStarsProgram();
private:
    TimerMs newColorTimer;
    TimerMs fadePixelTimer;

    std::set<Fader*, Fader> faders;
};

#endif /* RANDOMCOLORPROGRAM_H_ */
