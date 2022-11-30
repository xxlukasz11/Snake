#ifndef SRC_SNAKEMOVEMENTHANDLER_H_
#define SRC_SNAKEMOVEMENTHANDLER_H_

#include "snakeContext.h"
#include "worldMapContext.h"
#include "foodContext.h"

class GameContext;

class SnakeMovementHandler {
public:
	SnakeMovementHandler(GameContext& gameContext);
	void setSnakeSpeedIfValid(const SpeedVector& snakeSpeed);
	void moveSnake();
	bool gameEnded() const;
	void reset();

private:
	Position moveSnakeHead();
	void moveSnakeTailIfNecessary(const Position& newHeadPosition);
	bool handleBorderCollision(const Position& newHeadPosition);
	Position calculateNewHeadPosition();

	SnakeContext& snakeContext;
	FoodContext& foodContext;
	const WorldMapContext& worldMap;
	SpeedVector snakeSpeed;
};

#endif /* SRC_SNAKEMOVEMENTHANDLER_H_ */
