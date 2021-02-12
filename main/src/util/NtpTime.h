#ifndef NTPTIME_H_
#define NTPTIME_H_

#include <TimeLib.h>

namespace NtpTime {
/**
 * Get current time or 0 if not ready/known
 */
time_t getTime();
time_t nowToStruct(tmElements_t &tm);
}

#endif /* NTPTIME_H_ */
