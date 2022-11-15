#include <algorithm>
#include "foodContext.h"
#include "snakeContext.h"

namespace {
bool containsPos(const SnakeContext::Body& body, const Position& pos) {
	auto found = std::find_if(body.cbegin(), body.cend(), [pos](auto&& position) {
		return position == pos;
	});
	return found != body.cend();
}
}

FoodContext::FoodContext(const Area& availableArea) :
		generator(availableArea) {
}

void FoodContext::reset() {
	foodPosition.reset();
}

void FoodContext::placeFoodOnAvailableSquares(const SnakeContext& snakeContext) {
	const auto& forbiddenCoords = snakeContext.getBody();

	Position newFoodPosition;
	do {
		newFoodPosition.x = generator.ramdomX();
		newFoodPosition.y = generator.randomY();
	} while (containsPos(forbiddenCoords, newFoodPosition));

	foodPosition = newFoodPosition;
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

bool FoodContext::isFoodPlanted() const {
	return foodPosition.has_value();
}
