#ifndef WIFIWRAPPER_H_
#define WIFIWRAPPER_H_

#include "Service.h"

class WiFiWrapper: public Service {
private:
    const char *ssid;
    const char *password;
public:
    WiFiWrapper(const char *ssid, const char *password);
    void begin() override;
    void loop() override;
    virtual ~WiFiWrapper();
private:
    bool connectToWiFi();
    bool setUpAP();
};

#endif /* WIFIWRAPPER_H_ */
