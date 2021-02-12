#ifndef LEDSERVICE_H_
#define LEDSERVICE_H_

#include "../prog/ImageProgram.h"
#include "Service.h"

#include "../util/Leds.h"

class LedService: public Service {
private:
	ImageProgram *imageProgram;

	void deleteProgram();
public:
	LedService();
	void begin() override;
	void loop() override;

	void startNewProgram(ImageProgram *program);
	void drawPixel(uint8_t x, uint8_t y, CRGB &color);

	virtual ~LedService();
};

#endif /* LEDSERVICE_H_ */
