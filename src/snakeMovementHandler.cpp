#include "snakeMovementHandler.h"
#include "gameContext.h"

SnakeMovementHandler::SnakeMovementHandler(GameContext& gameContext) :
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		snakeDirection(Direction::NONE) {
}

void SnakeMovementHandler::setSnakeDirectionIfValid(const Direction& direction) {
	if (!snakeDirection.isOppositeTo(direction)) {
		snakeDirection = direction;
	}
}

void SnakeMovementHandler::moveSnake() {
	const auto newHeadPosition = moveSnakeHead();
	moveSnakeTailIfNecessary(newHeadPosition);
	// TODO: display animation when tail is cut off
	snakeContext.cutOffTailIfHeadCollided();
}

Vector2D SnakeMovementHandler::moveSnakeHead() {
	const auto newHeadPosition = calculateNewHeadPosition();
	snakeContext.appendHeadSegment(newHeadPosition);
	return newHeadPosition;
}

void SnakeMovementHandler::moveSnakeTailIfNecessary(const Vector2D& newHeadPosition) {
	if (foodContext.isFoodHere(newHeadPosition)) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	} else {
		snakeContext.eraseTailSegment();
	}
}

Vector2D SnakeMovementHandler::calculateNewHeadPosition() {
	const auto& headPosition = snakeContext.getHead();
	auto snakeSpeed = snakeDirection.getSpeedVector();
	return {headPosition.x + snakeSpeed.x, headPosition.y + snakeSpeed.y};
}

void SnakeMovementHandler::reset() {
	snakeDirection = Direction::NONE;
}
