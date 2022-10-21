#include "gameContext.h"

GameContext::GameContext(const Display& display, int rasterSize) :
		rasterSize(rasterSize),
		worldPainter(display, rasterSize),
		foodContext(calculateFoodArea(display, worldPainter.getBorderRasters())) {
}

AvailableArea GameContext::calculateFoodArea(const Display& display, int borderRasters) const {
	int horizontalRasters = display.width / rasterSize;
	int verticalRasters = display.height / rasterSize;
	Position topLeft{ borderRasters, borderRasters };
	Position bottomRight{ horizontalRasters - borderRasters, verticalRasters - borderRasters };
	return AvailableArea{ topLeft, bottomRight };
}

int GameContext::getRasterSize() const {
	return rasterSize;
}

const WorldPainter& GameContext::getWorldPainter() const {
	return worldPainter;
}

const SnakeContext& GameContext::getSnakeContext() const {
	return snakeContext;
}

SnakeContext& GameContext::getSnakeContext() {
	return snakeContext;
}

const FoodContext& GameContext::getFoodContext() const {
	return foodContext;
}

FoodContext& GameContext::getFoodContext() {
	return foodContext;
}
