#ifndef SERVICE_H_
#define SERVICE_H_

class Service {
public:
	virtual void begin() = 0;
	virtual void loop() = 0;
	virtual ~Service() {

	}
};

#endif /* SERVICE_H_ */
