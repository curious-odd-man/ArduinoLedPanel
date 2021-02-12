#ifndef LEDSERVICE_H_
#define LEDSERVICE_H_

#include "Service.h"

#include "../util/Leds.h"
#include "../prog/LightProgram.h"

class LedService: public Service {
private:
	LightProgram *imageProgram;

	void deleteProgram();
public:
	LedService();
	void begin() override;
	void loop() override;

	void startNewProgram(LightProgram *program);
	void drawPixel(uint8_t x, uint8_t y, CRGB &color);

	virtual ~LedService();
};

#endif /* LEDSERVICE_H_ */
