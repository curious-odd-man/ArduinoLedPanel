#ifndef POINT2D_H_
#define POINT2D_H_

#include <stdint.h>

template<class T>
class Point2d {
protected:
	T x;
	T y;
public:

	Point2d() :
			x(0), y(0) {
	}

	Point2d(T x, T y) :
			x(x), y(y) {
	}

	inline void move(const Point2d &vector) {
		x += vector.x;
		y += vector.y;
	}

	inline T getX() const {
		return x;
	}

	inline T getY() const {
		return y;
	}

	inline void setX(T x) {
		this->x = x;
	}

	inline void setY(T y) {
		this->y = y;
	}

	inline void invertX() {
		this->x = -x;
	}

	inline void invertY() {
		this->y = -y;
	}

	virtual ~Point2d() {

	}
};

#endif /* POINT2D_H_ */
