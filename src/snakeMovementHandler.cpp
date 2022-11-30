#include "snakeMovementHandler.h"
#include "gameContext.h"

SnakeMovementHandler::SnakeMovementHandler(GameContext& gameContext) :
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		worldMap(gameContext.getWorldMapContext()),
		snakeDirection(Direction::NONE) {
}

void SnakeMovementHandler::setSnakeDirectionIfValid(const Direction& direction) {
	auto snakeSpeed = snakeDirection.getSpeedVector();
	auto speed = direction.getSpeedVector();
	if (snakeSpeed.x != 0 && speed.x == -snakeSpeed.x) {
		return;
	}
	if (snakeSpeed.y != 0 && speed.y == -snakeSpeed.y) {
		return;
	}
	snakeDirection = direction;
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
	const auto& body = snakeContext.getBody();
	const auto& headPosition = body.at(0);
	auto snakeSpeed = snakeDirection.getSpeedVector();
	return {headPosition.x + snakeSpeed.x, headPosition.y + snakeSpeed.y};
}

void SnakeMovementHandler::reset() {
	snakeDirection = Direction::NONE;
}
