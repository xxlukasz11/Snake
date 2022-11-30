#include "gameContext.h"
#include "worldMapFrameBuilder.h"
#include "utils.h"
#include "framework/display.h"

using framework::Display;

namespace {

WorldMapContext createWorldMap(const Display& display) {
	Area screenArea = { { 0, 0 }, { display.getWidthRasters(), display.getHeightRasters() } };
	return WorldMapFrameBuilder::instance(screenArea).setFrameThickness(1).build();
}

} // namespace

GameContext::GameContext(const Display& display) :
		painter(display),
		worldMapContext(createWorldMap(display)),
		foodContext(worldMapContext),
		snakeMovementHandler(*this) {
}

void GameContext::reset() {
	snakeContext.reset();
	foodContext.reset();
	snakeMovementHandler.reset();
}

const WorldPainter& GameContext::getPainter() const {
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

SnakeMovementHandler& GameContext::getSnakeMovementHandler() {
	return snakeMovementHandler;
}
