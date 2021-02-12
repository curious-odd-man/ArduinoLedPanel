#include "RandomColorProgram.h"

using namespace std;

RandomColorProgram::RandomColorProgram() :
        newColorTimer(200), fadePixelTimer(10) {
    CRGB aqua = CRGB::Black;
    Leds::fillLeds(aqua);
}

void RandomColorProgram::loop() {
    if (newColorTimer.isReady()) {
        int r = random(255);
        int g = random(255);
        int b = random(255);
        int x = random(Leds::maxX() + 1);
        int y = random(Leds::maxY() + 1);
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

RandomColorProgram::~RandomColorProgram() {

}

