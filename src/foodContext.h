#ifndef SRC_FOODCONTEXT_H_
#define SRC_FOODCONTEXT_H_

#include <optional>
#include "utils.h"
#include "positionGenerator.h"

class SnakeContext;

class FoodContext {
public:
	FoodContext(const Area& availableArea);
	void placeFoodOnAvailableSquares(const SnakeContext& snakeContext);
	bool isFoodHere(const Position position) const;
	const std::optional<Position>& getFoodPositon() const;
	bool isFoodPlanted() const;

private:
	PositionGenerator generator;
	std::optional<Position> foodPosition;
};

#endif /* SRC_FOODCONTEXT_H_ */
