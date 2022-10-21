#ifndef SRC_FOODCONTEXT_H_
#define SRC_FOODCONTEXT_H_

#include <optional>
#include "position.h"

struct AvailableArea {
	Position topLeft;
	Position bottomRight;
};

class SnakeContext;

class FoodContext {
public:
	FoodContext(const AvailableArea& availableArea);
	void placeFoodOnAvailableSquares(const SnakeContext& snakeContext);
	bool isFoodHere(const Position position) const;

private:
	AvailableArea availableArea;
	std::optional<Position> foodPosition;
};

#endif /* SRC_FOODCONTEXT_H_ */
