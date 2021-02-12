#ifndef UDPQUERY_H_
#define UDPQUERY_H_

#include <IPAddress.h>

namespace UdpQuery {

bool sendRequest(const char* hostName, uint16_t port, const uint8_t *data, size_t len);
bool isRequestInProgress();
int isResponseReady();
int readResponse(uint8_t *data, size_t maxLen);
void setRequestCompleted();

}

#endif /* UDPQUERY_H_ */
