#ifndef TIMEPROGRAM_H_
#define TIMEPROGRAM_H_

#include "ImageProgram.h"
#include "../util/TimerMs.h"

class TimeProgram: public ImageProgram {
public:
    TimeProgram();
    virtual void loop() override;
    virtual ~TimeProgram();
private:
    TimerMs secondsTimer;
    TimerMs minutesTimer;
    bool drawDot = true;
    bool isInitialized = false;
};

#endif /* TIMEPROGRAM_H_ */
