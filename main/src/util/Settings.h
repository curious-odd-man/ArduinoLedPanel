#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <stdint.h>
#include <WString.h>

namespace PerMem {

void init();

uint8_t getLastVersionHash();
void saveLastVersionHash(uint8_t hash);

uint8_t getLastVersionSemaphore();
void setLastVersionSemaphore(uint8_t value);

void commit();

}

#endif /* SETTINGS_H_ */
