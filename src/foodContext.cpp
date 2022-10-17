#include <algorithm>
#include "foodContext.h"
#include "snakeContext.h"

namespace {
bool containsXPos(const SnakeContext::Body& body, int value) {
	auto found = std::find_if(body.cbegin(), body.cend(), [value](auto&& position) {
		return position.x == value;
	});
	return found != body.cend();
}
bool containsYPos(const SnakeContext::Body& body, int value) {
	auto found = std::find_if(body.cbegin(), body.cend(), [value](auto&& position) {
		return position.y == value;
	});
	return found != body.cend();
}
}

FoodContext::FoodContext(const Area& availableArea) :
		generator(availableArea) {
}

void FoodContext::placeFoodOnAvailableSquares(const SnakeContext& snakeContext) {
	const auto& forbiddenCoords = snakeContext.getBody();

	int x{ };
	do {
		x = generator.ramdomX();
	} while (containsXPos(forbiddenCoords, x));

	int y{ };
	do {
		y = generator.randomY();
	} while (containsYPos(forbiddenCoords, y));

	foodPosition = Position{ x, y };
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
