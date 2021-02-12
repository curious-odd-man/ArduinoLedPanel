#include "Arduino.h"
#include "common.h"
#include "WiFiUdp.h"
#include "UdpQuery.h"

namespace UdpQuery {

constexpr unsigned int UDP_LOCAL_PORT = 2390;
static WiFiUDP udp;
static bool requestInProgress = false;
static bool udpListening = false;

/**
 * Returns true if sent successfully, false otherwise
 */
bool sendRequest(const char* hostName, uint16_t port, const uint8_t *data, size_t len) {
    if (!udpListening) {
        uint8_t ok = udp.begin(UDP_LOCAL_PORT);
        LOGF("Started UDP listening: %s\n", ok == 1 ? "OK" : "Fail");
        udpListening = ok == 1;
        udp.flush();
    }

    if (requestInProgress) {
        return false;
    }

    requestInProgress = true;

    udp.beginPacket(hostName, port);
    udp.write(data, len);
    return udp.endPacket() == 1;
}

bool isRequestInProgress() {
    return requestInProgress;
}

/**
 * Returns size of packet, or 0
 */
int isResponseReady() {
    return udp.parsePacket();
}

/**
 * Returns number of bytes read.
 */
int readResponse(uint8_t *data, size_t maxLen) {
    return udp.read(data, maxLen);
}

void setRequestCompleted() {
    requestInProgress = false;
    udp.flush();
}

}
