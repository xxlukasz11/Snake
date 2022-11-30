#ifndef SRC_SNAKEMOVEMENTHANDLER_H_
#define SRC_SNAKEMOVEMENTHANDLER_H_

#include "snakeContext.h"
#include "worldMapContext.h"
#include "foodContext.h"

class GameContext;

class SnakeMovementHandler {
public:
	SnakeMovementHandler(GameContext& gameContext);
	void setSnakeSpeedIfValid(const Vector2D& snakeSpeed);
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
	Vector2D snakeSpeed;
};

#endif /* SRC_SNAKEMOVEMENTHANDLER_H_ */
