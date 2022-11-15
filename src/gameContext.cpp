#include "gameContext.h"
#include "worldMapFrameBuilder.h"
#include "utils.h"

namespace {

WorldMapContext createWorldMap(const Display& display) {
	Area screenArea = { { 0, 0 }, { display.widthRasters, display.heightRasters } };
	return WorldMapFrameBuilder::instance(screenArea).setFrameThickness(1).build();
}

} // namespace

GameContext::GameContext(const Display& display) :
		painter(display),
		worldMapContext(createWorldMap(display)),
		foodContext(worldMapContext) {
}

void GameContext::reset() {
	snakeContext.reset();
	foodContext.reset();
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
