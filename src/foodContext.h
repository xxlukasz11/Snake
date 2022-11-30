#ifndef SRC_FOODCONTEXT_H_
#define SRC_FOODCONTEXT_H_

#include <optional>
#include "utils.h"
#include "positionGenerator.h"
#include "worldMapContext.h"

class SnakeContext;

class FoodContext {
public:
	FoodContext(const WorldMapContext& worldMapContext);
	void reset();
	void placeFoodOnAvailableSquares(const SnakeContext& snakeContext);
	bool isFoodHere(const Vector2D position) const;
	const std::optional<Vector2D>& getFoodPositon() const;
	bool isFoodPlanted() const;

private:
	const WorldMapContext& worldMapContext;
	PositionGenerator generator;
	std::optional<Vector2D> foodPosition;
};

#endif /* SRC_FOODCONTEXT_H_ */
