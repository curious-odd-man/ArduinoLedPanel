#include "NtpTime.h"
#include "UdpQuery.h"
#include "IPAddress.h"
#include "WiFiUDP.h"

#include "TimerMs.h"

#include "common.h"
#include "Arduino.h"

namespace NtpTime {

static constexpr uint32_t TIME_SYNC_TIMEOUT = 24 * 60 * 60 * 1000;
static constexpr uint32_t NTP_RETRY_TIMEOUT = 30 * 1000;
static bool isInitialized = false;
static bool requestInProgress = false;
static TimerMs refreshTimer(NTP_RETRY_TIMEOUT);
static constexpr int8_t timeZoneOffset = 2;

const char *ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
uint8_t packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

static bool sendTimeRequest() {
    LOG("Sending NTP packet...");
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;        // LI, Version, Mode
    packetBuffer[1] = 0;        // Stratum, or type of clock
    packetBuffer[2] = 6;        // Polling Interval
    packetBuffer[3] = 0xEC;        // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    //get a random server from the pool
    return UdpQuery::sendRequest(ntpServerName, 123, packetBuffer, NTP_PACKET_SIZE);
}

static bool handleResonpse() {
    // We've received a packet, read the data from it
    LOG("Handling NTP response...");
    UdpQuery::readResponse(packetBuffer, NTP_PACKET_SIZE);
    UdpQuery::setRequestCompleted();

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    unsigned long seventyYears = 2208988800UL;
    time_t t = secsSince1900 - seventyYears + (timeZoneOffset) * 3600;
    setTime(t);
    return true;
}

time_t getTime() {
    if (isInitialized && !refreshTimer.isReady()) {
        LOG("Time already initialized!");
        return now();
    }

    if (requestInProgress) {
        // Retry request time if no response after timeout.
        if (!refreshTimer.isReady()) {
            LOG("Request in progress.. Awaiting response!");
            int len = UdpQuery::isResponseReady();
            if (len > 0) {
                LOG("Received NTP data...");
                bool ok = handleResonpse();
                if (ok) {
                    LOG("Successfully processed data...");
                    requestInProgress = false;
                    isInitialized = true;
                    refreshTimer.setInterval(TIME_SYNC_TIMEOUT);
                    refreshTimer.reset();
                    return now();
                } else {
                    LOG_ERROR("Failed to process data...\n");
                }
            }

            return 0;
        } else {
            UdpQuery::setRequestCompleted();
            LOG("Waited too long NTP response. Will retry.");
        }
    }

    requestInProgress = sendTimeRequest();
    refreshTimer.setInterval(NTP_RETRY_TIMEOUT);
    refreshTimer.reset();
    LOGF("Request sent: %s\n", requestInProgress ? "OK" : "Fail");
    return 0;
}

time_t nowToStruct(tmElements_t &tm) {
    time_t now = getTime();
    if (now != 0) {
        breakTime(now, tm);
        return now;
    } else {
        return 0;
    }
}

}
