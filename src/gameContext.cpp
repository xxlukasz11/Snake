#include "gameContext.h"

GameContext::GameContext(const Display& display, int rasterSize) :
		rasterSize(rasterSize),
		worldMap(display, rasterSize),
		foodContext(worldMap.calculateAvailableArea()) {
}

void GameContext::reset() {
	snakeContext.reset();
	foodContext.reset();
}

int GameContext::getRasterSize() const {
	return rasterSize;
}

const WorldMap& GameContext::getWorldMap() const {
	return worldMap;
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
