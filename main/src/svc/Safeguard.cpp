#include <Arduino.h>
#include <stdint.h>

#include "Safeguard.h"
#include "../util/Settings.h"
#include "../util/common.h"

constexpr uint8_t FAILURE_THRESHOLD = 5;
constexpr int APPLICATION_SAFENESS_TIMEOUT = 20 * 1000;     // 10 seconds

Safeguard::Safeguard() :
        safe(false), safenessTimer(APPLICATION_SAFENESS_TIMEOUT), semaforeValue(0), onTimer(true) {

}

void Safeguard::init(uint8_t compileDateHash) {
    LOGF("Version hash is 0x%x\n", compileDateHash);
    uint8_t lastVersionHash = PerMem::getLastVersionHash();
    LOGF("Previous runtime version is 0x%x\n", lastVersionHash);
    if (compileDateHash == lastVersionHash) {
        // Semaphore number increases on init and decreases after 10 seconds of application execution
        // If application fails/stops/crashes faster than 10 seconds, semaphore value will grow unless it exceeds threshold
        // At this point application is considered unsafe.
        semaforeValue = PerMem::getLastVersionSemaphore();
        LOGF("Latest semafore value is %d max is %d\n", semaforeValue, FAILURE_THRESHOLD);
        if (semaforeValue > FAILURE_THRESHOLD) {
            safe = false;
            onTimer = false;        // Do not reset semaphore, because version is not safe.
        } else {
            PerMem::setLastVersionSemaphore(semaforeValue + 1);
            safe = true;
        }
    } else {
        // New application version resets semaphore
        PerMem::saveLastVersionHash(compileDateHash);
        PerMem::setLastVersionSemaphore(1);
        safe = true;
    }
    if (onTimer) {
        PerMem::commit();
    }
}

inline void Safeguard::loop() {
    if (onTimer && safenessTimer.isReady()) {
        LOG("Safeness timer expired. Resetting semafore value to zero.\n");
        PerMem::setLastVersionSemaphore(0);
        onTimer = false;        // Only reset semaphore once
        PerMem::commit();
    }
}

