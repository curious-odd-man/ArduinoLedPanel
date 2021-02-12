#ifndef TIMERMS_H_
#define TIMERMS_H_

#include <stdint.h>

class TimerMs {
public:
	TimerMs(uint32_t interval, bool isStarted = true);

	void setInterval(uint32_t interval);
	bool isReady();
	void reset();
	virtual ~TimerMs();

private:
	uint32_t startTime = 0;
	uint32_t interval = 0;
};

#endif /* TIMERMS_H_ */
