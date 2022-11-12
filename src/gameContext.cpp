#include "gameContext.h"

GameContext::GameContext(const Display& display, int rasterSize) :
		rasterSize(rasterSize),
		painter(display, rasterSize),
		foodContext(painter.calculateAvailableArea()) {
}

void GameContext::reset() {
	snakeContext.reset();
	foodContext.reset();
}

int GameContext::getRasterSize() const {
	return rasterSize;
}

const WorldMapPainter& GameContext::getPainter() const {
	return painter;
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

const WorldMapContext& GameContext::getWorldMapContext() const {
	return worldMapContext;
}
