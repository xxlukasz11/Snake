#include "snakeMovementHandler.h"
#include "gameContext.h"

SnakeMovementHandler::SnakeMovementHandler(GameContext& gameContext) :
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		worldMap(gameContext.getWorldMapContext()) {
}

void SnakeMovementHandler::moveSnake() {
	const auto newHeadPosition = moveSnakeHead();
	moveSnakeTailIfNecessary(newHeadPosition);
	// TODO: display animation when tail is cut off
	snakeContext.cutOffTailIfHeadCollided();
}

bool SnakeMovementHandler::gameEnded() const {
	if (worldMap.isBorderHere(snakeContext.getBody()[0])) {
		return true;
	}
	return false;
}

Position SnakeMovementHandler::moveSnakeHead() {
	const auto newHeadPosition = calculateNewHeadPosition();
	snakeContext.appendHeadSegment(newHeadPosition);
	return newHeadPosition;
}

void SnakeMovementHandler::moveSnakeTailIfNecessary(const Position& newHeadPosition) {
	if (foodContext.isFoodHere(newHeadPosition)) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	} else {
		snakeContext.eraseTailSegment();
	}
}

Position SnakeMovementHandler::calculateNewHeadPosition() {
	const auto& speed = snakeContext.getSpeed();
	const auto& body = snakeContext.getBody();
	const auto& headPosition = body.at(0);
	return {headPosition.x + speed.x, headPosition.y + speed.y};
}
