#ifndef SRC_SNAKECONTEXT_H_
#define SRC_SNAKECONTEXT_H_

#include <deque>
#include <optional>
#include "color.h"
#include "utils.h"

class SnakeContext {
public:
	using Body = std::deque<Vector2D>;

	void reset();
	const Color& getHeadColor() const;
	const Color& getBodyColor() const;
	const Body& getBody() const;
	const Vector2D& getHead() const;
	int getSnakeSize() const;
	void cutOffTailIfHeadCollided();
	void appendHeadSegment(const Vector2D& headPosition);
	void eraseTailSegment();

private:
	Body body;
};

#endif /* SRC_SNAKECONTEXT_H_ */
