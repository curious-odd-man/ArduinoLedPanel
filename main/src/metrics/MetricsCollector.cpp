#include "MetricsCollector.h"

#ifdef COLLECT_METRIX

#include <Arduino.h>
#include <WString.h>
#include <vector>
#include <limits.h>
#include <map>

/**
 * Some documentation:
 * https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#esp-specific-apis
 */

namespace MetricsCollector {
using namespace std;

static std::map<unsigned int, unsigned long> loopTimesCounter;

static void initLoopTimesCounter() {
	loopTimesCounter[35] = 0;
	loopTimesCounter[50] = 0;
	loopTimesCounter[100] = 0;
	loopTimesCounter[200] = 0;
	loopTimesCounter[500] = 0;
	loopTimesCounter[1000] = 0;
	loopTimesCounter[5000] = 0;
	loopTimesCounter[10000] = 0;
	loopTimesCounter[15000] = 0;
	loopTimesCounter[20000] = 0;
	loopTimesCounter[100000] = 0;
}

void init() {
	initLoopTimesCounter();
}

static constexpr unsigned long subtract(unsigned long start,
		unsigned long end) {
	return end >= start ? end - start : ULONG_MAX - end + start;
}

static constexpr const char* reportTimeHead() {
	return "# TYPE esp8266_report_time gauge\n"
			"esp8266_report_time ";
}

static constexpr const char* heapFreeHead() {
	return "# TYPE esp8266_heap_free gauge\n"
			"esp8266_heap_free ";
}

static constexpr const char* heapMaxHead() {
	return "# TYPE esp8266_heap_max gauge\n"
			"esp8266_heap_max ";
}

static constexpr const char* heapFragHead() {
	return "# TYPE esp8266_heap_frag gauge\n"
			"esp8266_heap_frag ";
}

static constexpr const char* vccHead() {
	return "# TYPE esp8266_vcc gauge\n"
			"esp8266_vcc ";
}

static void logLoopTime(unsigned long t) {
	auto it = loopTimesCounter.upper_bound(t);
	if (it == loopTimesCounter.end()) {
		--it;
	}
	++it->second;
}

void logLoopTotalTime(unsigned long start, unsigned long end) {
	logLoopTime(subtract(start, end));
}

static const String makeLoopTimeHistogram() {
	String s = "# TYPE esp8266_loop_time histogram\n";
	s.reserve(100 * loopTimesCounter.size());

	for (auto const &pair : loopTimesCounter) {
		s += "esp8266_loop_time{lt=\"";
		s += pair.first;
		s += "\"} ";
		s += pair.second;
		s += '\n';
	}

	initLoopTimesCounter();
	return s;
}

String getPrometheusOutput() {
	unsigned long start = micros();

	String message = "";
	message.reserve(1024);		// Just a guess

	message += makeLoopTimeHistogram();

	uint32_t free;
	uint16_t max;
	uint8_t frag;
	ESP.getHeapStats(&free, &max, &frag);

	message += heapFreeHead();
	message += free;
	message += "\n";

	message += heapMaxHead();
	message += max;
	message += "\n";

	message += heapFragHead();
	message += frag;
	message += "\n";

	uint16_t vcc = ESP.getVcc();
	message += vccHead();
	message += vcc;
	message += "\n";

	message += reportTimeHead();
	message += subtract(start, micros());
	message += "\n";

	return message;
}

}

#endif

