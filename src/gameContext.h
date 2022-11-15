#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldMapContext.h"
#include "worldPainter.h"

class GameContext {
public:
	GameContext(const Display& display);

	void reset();
	const WorldPainter& getPainter() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();
	const WorldMapContext& getWorldMapContext() const;

private:
	WorldPainter painter;
	SnakeContext snakeContext;
	FoodContext foodContext;
	WorldMapContext worldMapContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
