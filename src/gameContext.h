#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "snakeContext.h"
#include "foodContext.h"
#include "worldMapContext.h"
#include "worldPainter.h"

namespace framework {
class Display;
}

class GameContext {
public:
	GameContext(const framework::Display& display);

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
	WorldMapContext worldMapContext;
	FoodContext foodContext;
};

#endif /* SRC_GAMECONTEXT_H_ */
