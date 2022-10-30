#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldMap.h"

class GameContext {
public:
	GameContext(const Display& display, int rasterSize);

	void reset();
	int getRasterSize() const;
	const WorldMap& getWorldMap() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();

private:
	int rasterSize;
	WorldMap worldMap;
	SnakeContext snakeContext;
	FoodContext foodContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
