#ifndef ROLLINGBALLPROGRAM_H_
#define ROLLINGBALLPROGRAM_H_

#include "LightProgram.h"
#include "../util/Point2d.h"

class RollingBallProgram: public LightProgram {
public:
    RollingBallProgram(uint8_t size);
    virtual void loop() override;
    virtual ~RollingBallProgram();
private:
    Point2d<float> position;
    Point2d<float> movement;
    uint8_t size;
};
#endif /* ROLLINGBALLPROGRAM_H_ */
