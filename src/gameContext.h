#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"
#include "worldPainter.h"
#include "foodContext.h"

class GameContext {
public:
	GameContext(const Display& display, int rasterSize);

	int getRasterSize() const;
	const WorldPainter& getWorldPainter() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();

private:
	Area calculateFoodArea(const Display& display, int borderRasters) const;

	int rasterSize;
	WorldPainter worldPainter;
	SnakeContext snakeContext;
	FoodContext foodContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
