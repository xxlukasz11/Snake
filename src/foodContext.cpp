#include <random>
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
	return found == body.cend();
}
}

FoodContext::FoodContext(const Area& availableArea) :
		availableArea(availableArea) {
}

void FoodContext::placeFoodOnAvailableSquares(const SnakeContext& snakeContext) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<> xDistrib(availableArea.topLeft.x, availableArea.bottomRight.x);
	std::uniform_int_distribution<> yDistrib(availableArea.topLeft.y, availableArea.bottomRight.y);

	const auto& forbiddenCoords = snakeContext.getBody();

	int x{ };
	do {
		x = xDistrib(generator);
	} while (containsXPos(forbiddenCoords, x));

	int y{ };
	do {
		y = xDistrib(generator);
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
