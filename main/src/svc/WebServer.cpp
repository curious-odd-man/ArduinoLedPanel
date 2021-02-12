#include <WString.h>

#include "WebServer.h"
#include "../util/Leds.h"
#include "../prog/Effects.h"
#include "../util/common.h"
#include "../metrics/MetricsCollector.h"


using namespace std;

String modes = "";

extern const char index_html[];
extern const char main_js[];

WebServer::WebServer(int port, LedService &ledSerivce) :
		server(port), ledService(ledSerivce) {
}

void WebServer::begin() {
	modes_setup();
	server.on(Uri("/"), std::bind(&WebServer::srv_handle_index_html, this));
	server.on(Uri("/main.js"), std::bind(&WebServer::srv_handle_main_js, this));
	server.on(Uri("/modes"), std::bind(&WebServer::srv_handle_modes, this));
	server.on(Uri("/set"), std::bind(&WebServer::srv_handle_set, this));
#ifdef COLLECT_METRIX
	server.on(Uri("/prometheus"), std::bind(&WebServer::srv_prometheus, this));
#endif
	server.onNotFound(std::bind(&WebServer::srv_handle_not_found, this));
	server.begin();
}

#ifdef COLLECT_METRIX
void WebServer::srv_prometheus() {
	server.send(200, "text/plain", MetricsCollector::getPrometheusOutput());
}
#endif

void WebServer::srv_handle_not_found() {
	server.send(404, "text/plain", "File Not Found");
}

void WebServer::srv_handle_index_html() {
	server.send_P(200, "text/html", index_html);
}

void WebServer::srv_handle_main_js() {
	server.send_P(200, "application/javascript", main_js);
}

void WebServer::srv_handle_modes() {
	server.send(200, "text/plain", modes);
}

static int currentProgram = -1;

typedef std::function<LightProgram* ()> ProgSupplier;

static const ProgSupplier suppliers[] = { []() {
	return new RunningTextProgram("Hello Alina! Моя любимая женушка!",
			CRGB(CRGB::DarkSeaGreen));
},
[]() {
	return new SnowProgram();
},
[]() {
	return new TimeProgram();
} };

void WebServer::srv_handle_set() {
	std::map<String, String> arguments;
	for (uint8_t i = 0; i < server.args(); i++) {
		arguments.insert(
				std::pair<String, String>(server.argName(i).c_str(),
						server.arg(i).c_str()));
	}

	auto it = arguments.find("m");

	if (it != arguments.end()) {
		LOGF("Found 'm' parameter with value: %s\n", (*it).second.c_str());
	}
//        if (server.argName(i) == "c") {
//            uint32_t tmp = (uint32_t) strtol(server.arg(i).c_str(), NULL, 10);
//            if (tmp >= 0x000000 && tmp <= 0xFFFFFF) {
//                CRGB color(tmp);
//                // TODO: Maybe we should not always re-allocate the object?
//                // Probably we can have method - canChangeColor() and then setColor() to a current program.
//                ledService.startNewProgram(new SolidColorProgram(color));
//            }
//        }
//
//        if (server.argName(i) == "m") {
//            uint8_t tmp = (uint8_t) strtol(server.arg(i).c_str(), NULL, 10);
//        }
//
//        if (server.argName(i) == "b") {
//            if (server.arg(i)[0] == '-') {
//                Leds::decrementBrightness();
//            } else {
//                Leds::incrementBrightness();
//            }
//        }
//
//        if (server.argName(i) == "s") {
//
//        }
//
//        if (server.argName(i) == "a") {
//            if (server.arg(i)[0] == '-') {
//            } else {
//            }
//        }

	currentProgram = (++currentProgram)
			% (sizeof(suppliers) / sizeof(ProgSupplier));
	ledService.startNewProgram(suppliers[currentProgram]());

	/** FIXME
	 *      if (hasNewProgram()) {
	 // What to show
	 ledService->startNewProgram(webServer->getNewProgram());
	 }
	 */
	server.send(200, "text/plain", "OK");
}

void WebServer::modes_setup() {
	modes = "";
	for (uint8_t i = 0; i < 1; i++) {
		modes += "<li><a href='#'>";
		modes += "Rolling Ball Program";
		modes += "</a></li>";
	}
}

void WebServer::loop() {
	server.handleClient();
}

WebServer::~WebServer() {
}

