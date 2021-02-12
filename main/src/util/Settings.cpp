#include <Arduino.h>
#include <ESP_EEPROM.h>
#include "Settings.h"
#include "common.h"

using namespace PerMem;

/* List of addresses used to store data in EEPROM */
constexpr uint16_t LAST_PROGRAM_ID = 0;
constexpr uint16_t LAST_VERSION_HASH = 1;
constexpr uint16_t LAST_VERSION_SEMAPHORE = 2;
/* End of List of addresses */

// https://arduino-esp8266.readthedocs.io/en/latest/libraries.html

namespace PerMem {

void writeHard(uint16_t addr, uint8_t value) {
    EEPROM.write(addr, value);
    bool ok = EEPROM.commit();
    LOG(((ok) ? "Commit OK" : "Commit failed"));
}

void init() {
    LOG("Initialization of EEPROM.");
    EEPROM.begin(512);
}

uint8_t getLastVersionHash() {
    return EEPROM.read(LAST_VERSION_HASH);
}

void saveLastVersionHash(uint8_t hash) {
    EEPROM.write(LAST_VERSION_HASH, (uint8_t) hash);
}

uint8_t getLastVersionSemaphore() {
    return EEPROM.read(LAST_VERSION_SEMAPHORE);
}

void setLastVersionSemaphore(uint8_t value) {
    EEPROM.write(LAST_VERSION_SEMAPHORE, (uint8_t) value);
}

void commit() {
    bool ok = EEPROM.commit();
    LOG(((ok) ? "Commit OK" : "Commit failed"));
}

}

