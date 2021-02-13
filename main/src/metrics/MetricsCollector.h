//#define COLLECT_METRIX

#ifndef SRC_METRICS_METRICSCOLLECTOR_H_
#define SRC_METRICS_METRICSCOLLECTOR_H_

#ifdef COLLECT_METRIX

#include <WString.h>

namespace MetricsCollector {
void init();
String getPrometheusOutput();

void logLoopTotalTime(unsigned long start, unsigned long end);

}

#endif

#endif /* SRC_METRICS_METRICSCOLLECTOR_H_ */
