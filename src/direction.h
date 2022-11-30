#ifndef SRC_DIRECTION_H_
#define SRC_DIRECTION_H_

#include "utils.h"

class Direction {
public:
	Vector2D getSpeedVector() const;
	bool isOppositeTo(const Direction& direction);

	static Direction UP;
	static Direction DOWN;
	static Direction LEFT;
	static Direction RIGHT;
	static Direction NONE;

private:
	Direction(const Vector2D& speedVector);
	Vector2D speedVector;
};

#endif /* SRC_DIRECTION_H_ */
