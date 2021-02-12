#include "SolidColorProgram.h"

#include "../util/common.h"


SolidColorProgram::SolidColorProgram(CRGB color) :
        color(color), isSet(false) {

}

void SolidColorProgram::loop() {
    if (!isSet) {
        isSet = true;
        Leds::fillLeds(color);
    }
}

SolidColorProgram::~SolidColorProgram() {
}

