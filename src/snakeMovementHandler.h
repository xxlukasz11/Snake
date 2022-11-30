#ifndef SRC_SNAKEMOVEMENTHANDLER_H_
#define SRC_SNAKEMOVEMENTHANDLER_H_

#include "snakeContext.h"
#include "worldMapContext.h"
#include "foodContext.h"
#include "direction.h"

class GameContext;

class SnakeMovementHandler {
public:
	SnakeMovementHandler(GameContext& gameContext);
	void setSnakeDirectionIfValid(const Direction& direction);
	void moveSnake();
	bool gameEnded() const;
	void reset();

private:
	Vector2D moveSnakeHead();
	void moveSnakeTailIfNecessary(const Vector2D& newHeadPosition);
	bool handleBorderCollision(const Vector2D& newHeadPosition);
	Vector2D calculateNewHeadPosition();

	SnakeContext& snakeContext;
	FoodContext& foodContext;
	const WorldMapContext& worldMap;
	Direction snakeDirection;
};

#endif /* SRC_SNAKEMOVEMENTHANDLER_H_ */
