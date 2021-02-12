#include <Arduino.h>
#include "TimerMs.h"

TimerMs::TimerMs(uint32_t interval, bool isStarted) {
    this->interval = interval;
    startTime = millis();
    if (!isStarted) {
        startTime -= interval;
    }
}

void TimerMs::setInterval(uint32_t interval) {
    this->interval = interval;
}

bool TimerMs::isReady() {
    if (millis() - startTime >= interval) {
        startTime = millis();
        return true;
    } else {
        return false;
    }
}

void TimerMs::reset() {
    startTime = millis();
}

TimerMs::~TimerMs() {
}
