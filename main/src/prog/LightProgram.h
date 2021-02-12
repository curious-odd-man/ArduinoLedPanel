#ifndef LIGHTPROGRAM_H_
#define LIGHTPROGRAM_H_

class LightProgram {
public:

    LightProgram();
    virtual ~LightProgram();
    virtual void loop() = 0;
};

#endif
