#define COLLECT_METRIX

#ifndef SRC_METRICS_METRICSCOLLECTOR_H_
#define SRC_METRICS_METRICSCOLLECTOR_H_

#ifdef COLLECT_METRIX

#include <string>

namespace MetricsCollector {

std::string getPrometheusOutput();

void logLoopTotalTime(long ms);



}

#endif

#endif /* SRC_METRICS_METRICSCOLLECTOR_H_ */
