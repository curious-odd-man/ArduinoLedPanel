#include "WiFiWrapper.h"
#include <ESP8266WiFi.h>

#include "../util/common.h"

const char PROGMEM apName[] = "MyLamp";
const char PROGMEM apPass[] = "BadgerPass";		//FIXME

WiFiWrapper::WiFiWrapper(const char *ssid, const char *password) {
	this->ssid = ssid;
	this->password = password;
}

bool WiFiWrapper::connectToWiFi() {
	WiFi.mode(WIFI_STA);
	LOGF("Connecting to %s\n", this->ssid);
	WiFi.begin(this->ssid, this->password);
	return WiFi.waitForConnectResult() == WL_CONNECTED;
}

bool WiFiWrapper::setUpAP() {
	WiFi.softAPdisconnect(true);

	LOGF("Creating access point %s\n", apName);

	bool ap_connected = WiFi.softAP(apName, apPass);
	if (ap_connected) {
		LOGF("IP address: %s\n", WiFi.softAPIP().toString().c_str());
		return true;
	}
	LOG("Failed to create AP");
	return false;
}

void WiFiWrapper::begin() {
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	WiFi.disconnect(true);
	if (!connectToWiFi()) {
		if (!setUpAP()) {
			LOG("No WiFi by any means");
			return;
		}
	}

	LOG(WiFi.localIP());
}

void WiFiWrapper::loop() {

}

WiFiWrapper::~WiFiWrapper() {

}

