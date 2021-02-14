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
};

#endif /* RUNNINGTEXTPROGRAM_H_ */
