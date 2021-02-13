#ifndef SAFEGUARD_H_
#define SAFEGUARD_H_

#include "Service.h"
#include "../util/TimerMs.h"

class Safeguard: public Service {
public:
	Safeguard();
	inline bool isSafe() {
		return safe;
	}

	void init(uint8_t compileDateHash);
	virtual void begin() override {
	}

	virtual void loop() override;
	virtual ~Safeguard() {
	}

private:
	bool safe;
	TimerMs safenessTimer;
	uint8_t semaforeValue;
	bool onTimer;
};

#endif /* SAFEGUARD_H_ */
