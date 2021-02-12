#ifndef ARDUINOOTAWRAPPER_H_
#define ARDUINOOTAWRAPPER_H_

#include "../svc/Service.h"

class ArduinoOtaWrapper: public Service {
public:
	ArduinoOtaWrapper();
	void begin() override;
	void loop() override;
	virtual ~ArduinoOtaWrapper();
};

#endif /* ARDUINOOTAWRAPPER_H_ */
