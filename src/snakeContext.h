#ifndef SRC_SNAKECONTEXT_H_
#define SRC_SNAKECONTEXT_H_

#include <deque>
#include "color.h"
#include "utils.h"

struct SpeedVector {
	int x;
	int y;
};

class SnakeContext {
public:
	using Body = std::deque<Position>;

	void reset();
	const Color& getHeadColor() const;
	const Color& getBodyColor() const;
	const Body& getBody() const;
	const SpeedVector& getSpeed() const;
	int getSnakeSize() const;
	bool isHeadOverBodySegment() const;

	void setSpeed(const SpeedVector& newSpeed);
	void appendHeadSegment(const Position& headPosition);
	void eraseTailSegment();

private:
	SpeedVector speed{ 0, 0 };
	Body body;
};

#endif /* SRC_SNAKECONTEXT_H_ */
