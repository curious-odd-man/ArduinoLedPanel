#ifndef COMMON_H_
#define COMMON_H_

#include <algorithm>
#include <Arduino.h>

using namespace std;

#define min(a,b) min(a, b)
#define max(a,b) max(a, b)

#define LOGGING_INIT Serial.begin(115200)

#define LOGLINE(x) Serial.printf("[%s] %s:%d\t", x, __FILE__, __LINE__)

#define LOG_ERROR(x)       LOGLINE("ERR"); Serial.println(x)
#define LOGF_ERROR(x, ...) LOGLINE("ERR"); Serial.printf(x, __VA_ARGS__)
#define LOG(x)             LOGLINE("INF"); Serial.println(x)
#define LOGF(x, ...)       LOGLINE("INF"); Serial.printf(x, __VA_ARGS__)
#define LOG_COLOR(t, c)    LOGLINE("INF"); Serial.printf("Color: 0x%02x%02x%02x. %s", c.r, c.g, c.b, t)

inline float randomFloat(float x, float y) {
	return ((float) random(x * 1000, y * 1000)) / 1000.0;
}

#endif /* COMMON_H_ */
