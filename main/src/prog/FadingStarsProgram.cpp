#include "FadingStarsProgram.h"

using namespace std;

FadingStarsProgram::FadingStarsProgram() :
        newColorTimer(200), fadePixelTimer(10) {
    CRGB aqua = CRGB::Black;
    Leds::fillLeds(aqua);
}

void FadingStarsProgram::loop() {
    if (newColorTimer.isReady()) {
        int r = random(255);
        int g = random(255);
        int b = random(255);
        int x = random(Leds::width());
        int y = random(Leds::height());
        Fader *fader = new Fader(CRGB(r, g, b), x, y);

        pair<set<Fader*>::iterator, bool> ret = faders.insert(fader);
        if (ret.second) {
            Leds::drawPixel(x, y, (*ret.first)->color);
        } else {
            newColorTimer.reset();
        }
    }

    if (fadePixelTimer.isReady()) {
        for (set<Fader*>::iterator it = faders.begin(); it != faders.end(); ++it) {
            Fader *value = *it;
            value->color.fadeToBlackBy(1);
            Leds::drawPixel(value->x, value->y, value->color);
        }

        for (auto it = faders.begin(), last = faders.end(); it != last;) {
            if ((*it)->is_black()) {
                delete (*it);
                it = faders.erase(it);
            } else {
                ++it;
            }
        }
    }
}

FadingStarsProgram::~FadingStarsProgram() {

}

