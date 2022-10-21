#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"
#include "foodContext.h"
#include "wolrdMap.h"

class GameContext {
public:
	GameContext(const Display& display, int rasterSize);

	int getRasterSize() const;
	const WolrdMap& getWolrdMap() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();

private:
	Area calculateFoodArea(const Display& display, int borderRasters) const;

	int rasterSize;
	WolrdMap wolrdMap;
	SnakeContext snakeContext;
	FoodContext foodContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
