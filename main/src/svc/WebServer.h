#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "Service.h"
#include "LedService.h"
#include "../metrics/MetricsCollector.h"

class WebServer: public Service {
public:
    WebServer(int port, LedService &ledSerivce);
    void begin() override;
    void loop() override;
    virtual ~WebServer();
private:
    ESP8266WebServer server;
    LedService &ledService;

    void srv_handle_not_found();
    void srv_handle_index_html();
    void srv_handle_main_js();
    void srv_handle_modes();
    void srv_handle_set();
#ifdef COLLECT_METRIX
	void srv_prometheus();
#endif
    void modes_setup();
};

#endif /* WEBSERVER_H_ */
