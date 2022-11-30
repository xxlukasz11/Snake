#ifndef SRC_SNAKEMOVEMENTHANDLER_H_
#define SRC_SNAKEMOVEMENTHANDLER_H_

#include "snakeContext.h"
#include "worldMapContext.h"
#include "foodContext.h"

class GameContext;

class SnakeMovementHandler {
public:
	SnakeMovementHandler(GameContext& gameContext);
	// TODO: void updateSnakeSpeed()
	void moveSnake();
	bool gameEnded() const;

private:
	Position moveSnakeHead();
	void moveSnakeTailIfNecessary(const Position& newHeadPosition);
	bool handleBorderCollision(const Position& newHeadPosition);
	Position calculateNewHeadPosition();

	SnakeContext& snakeContext;
	FoodContext& foodContext;
	const WorldMapContext& worldMap;
};

#endif /* SRC_SNAKEMOVEMENTHANDLER_H_ */
