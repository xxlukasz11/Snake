#ifndef SRC_SNAKECONTEXT_H_
#define SRC_SNAKECONTEXT_H_

#include <deque>
#include <optional>
#include "color.h"
#include "utils.h"

// TODO: move it to different place
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
	int getSnakeSize() const;
	void cutOffTailIfHeadCollided();
	void appendHeadSegment(const Position& headPosition);
	void eraseTailSegment();

private:
	Body body;
};

#endif /* SRC_SNAKECONTEXT_H_ */
