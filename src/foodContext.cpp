#include <algorithm>
#include "foodContext.h"
#include "snakeContext.h"
#include "worldMapContext.h"

namespace {
bool containsPos(const SnakeContext::Body& body, const Vector2D& pos) {
	auto found = std::find_if(body.cbegin(), body.cend(), [pos](auto&& position) {
		return position == pos;
	});
	return found != body.cend();
}
}

FoodContext::FoodContext(const WorldMapContext& worldMapContext) :
		worldMapContext(worldMapContext),
		generator(worldMapContext.getFoodArea()) {
}

void FoodContext::reset() {
	foodPosition.reset();
}

void FoodContext::placeFoodOnAvailableSquares(const SnakeContext& snakeContext) {
	const auto& forbiddenCoords = snakeContext.getBody();

	Vector2D newFoodPosition;
	do {
		newFoodPosition.x = generator.randomX();
		newFoodPosition.y = generator.randomY();
	} while (containsPos(forbiddenCoords, newFoodPosition) || worldMapContext.isBorderHere(newFoodPosition));

	foodPosition = newFoodPosition;
}

bool FoodContext::isFoodHere(const Vector2D position) const {
	if (foodPosition.has_value()) {
		return position == foodPosition.value();
	}
	return false;
}

const std::optional<Vector2D>& FoodContext::getFoodPositon() const {
	return foodPosition;
}

bool FoodContext::isFoodPlanted() const {
	return foodPosition.has_value();
}
