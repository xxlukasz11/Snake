#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldMapContext.h"
#include "worldMapPainter.h"

class GameContext {
public:
	GameContext(const Display& display, int rasterSize);

	void reset();
	int getRasterSize() const;
	const WorldMapPainter& getPainter() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();
	const WorldMapContext& getWorldMapContext() const;

private:
	int rasterSize;
	WorldMapPainter painter;
	SnakeContext snakeContext;
	FoodContext foodContext;
	WorldMapContext worldMapContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
