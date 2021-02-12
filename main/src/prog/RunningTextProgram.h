#ifndef RUNNINGTEXTPROGRAM_H_
#define RUNNINGTEXTPROGRAM_H_

#include "ImageProgram.h"
#include "WString.h"

#include "../util/TimerMs.h"
#include "../util/Leds.h"


class RunningTextProgram: public ImageProgram {
public:
    RunningTextProgram(const char* text, const CRGB &color);
    virtual void loop() override;
    virtual ~RunningTextProgram();
private:
    int offset;
    TimerMs scrollTimer;
    const char* text;
    CRGB color;

    void drawLetter(uint8_t letter, int16_t offset, const CRGB& color);
    uint8_t getLetterByte(uint8_t font, uint8_t row);
};

#endif /* RUNNINGTEXTPROGRAM_H_ */
