#ifndef SRC_SNAKECONTEXT_H_
#define SRC_SNAKECONTEXT_H_

#include <deque>
#include <allegro5/allegro_color.h>

#include "utils.h"

struct SpeedVector {
	int x;
	int y;
};

class SnakeContext {
public:
	using Body = std::deque<Position>;

	const ALLEGRO_COLOR& getHeadColor() const;
	const ALLEGRO_COLOR& getBodyColor() const;
	const Body& getBody() const;
	const SpeedVector& getSpeed() const;

	void setSpeed(const SpeedVector& newSpeed);
	void appendHeadSegment(const Position& headPosition);
	void eraseTailSegment();

private:
	SpeedVector speed{ 0, 0 };
	Body body;
};

#endif /* SRC_SNAKECONTEXT_H_ */
