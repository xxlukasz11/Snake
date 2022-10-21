#include "foodContext.h"
#include "snakeContext.h"

FoodContext::FoodContext(const Area& availableArea) :
		availableArea(availableArea) {
}

void FoodContext::placeFoodOnAvailableSquares(const SnakeContext& snakeContext) {
	// TODO place food randomly
	foodPosition = Position{ 25, 25 };
}

bool FoodContext::isFoodHere(const Position position) const {
	if (foodPosition.has_value()) {
		return position == foodPosition.value();
	}
	return false;
}

const std::optional<Position>& FoodContext::getFoodPositon() const {
	return foodPosition;
}
