#ifndef LEDS_SOLIDCOLORPROGRAM_H_
#define LEDS_SOLIDCOLORPROGRAM_H_

#include "LightProgram.h"
#include "../util/Leds.h"

class SolidColorProgram: public LightProgram {
private:
    CRGB color;
    bool isSet;
public:
    SolidColorProgram(CRGB color);
    virtual void loop() override;
    virtual ~SolidColorProgram();

};

#endif /* LEDS_SOLIDCOLORPROGRAM_H_ */
