#include <list>
#include <Arduino.h>
#include "src/svc/WebServer.h"

#include "src/util/common.h"
#include "src/util/Settings.h"
#include "src/util/Leds.h"
#include "src/util/TimerMs.h"
#include "src/util/hash.h"
#include "src/svc/WiFiWrapper.h"
#include "src/ota/ArduinoOtaWrapper.h"
#include "src/svc/LedService.h"
#include "src/svc/Safeguard.h"
#include "src/SensitiveInformation.h"

using namespace std;

constexpr char compile_date[] = __DATE__ " " __TIME__;

constexpr int HTTP_PORT = 80;

static LedService ledService = LedService();
static WebServer webServer(HTTP_PORT, ledService);
static WiFiWrapper wifiWrapper = WiFiWrapper(ssid, password);
static ArduinoOtaWrapper otaWrapper = ArduinoOtaWrapper();

static list<Service*> services;
static TimerMs watchdogFeedTimer(1000);

static Safeguard safeguard;

void setup() {
	randomSeed(analogRead(0));
	LOGGING_INIT;
	delay(10);		// Give some time to start up serial

	LOGF("Booting. Version-@%s\n", compile_date);
	PerMem::init();
	uint8_t compileDateHash = getHash(compile_date, sizeof(compile_date));

	safeguard.init(compileDateHash);

	if (safeguard.isSafe()) {
		LOG("This is safe software. Running all services...");
		services.push_back(&wifiWrapper);
		services.push_back(&otaWrapper);
		services.push_back(&webServer);
		services.push_back(&ledService);
	} else {
		LOG(
				"The software was detected as unsafe!! Only WiFi and OTA services are running!!!\nLoad new version of software to solve this issue.");
		services.push_back(&wifiWrapper);
		services.push_back(&otaWrapper);
	}

	for (Service *service : services) {
		service->begin();
	}

	LOG("Setup complete");
}

void loop() {
	for (Service *service : services) {
		service->loop();
	}

	Leds::loop();

	if (watchdogFeedTimer.isReady()) {
		ESP.wdtFeed();
	}

	safeguard.loop();
}
