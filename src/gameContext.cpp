#include "gameContext.h"

GameContext::GameContext(const Display& display, int rasterSize) :
		rasterSize(rasterSize),
		worldPainter(display, rasterSize) {
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
