#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "snakeContext.h"
#include "foodContext.h"
#include "worldMapContext.h"
#include "worldPainter.h"
#include "snakeMovementHandler.h"

namespace allegrocpp {
class Display;
}

class GameContext {
public:
	GameContext(const allegrocpp::Display& display);

	void reset();
	const WorldPainter& getPainter() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();
	const FoodContext& getFoodContext() const;
	FoodContext& getFoodContext();
	const WorldMapContext& getWorldMapContext() const;
	SnakeMovementHandler& getSnakeMovementHandler();

private:
	WorldPainter painter;
	SnakeContext snakeContext;
	WorldMapContext worldMapContext;
	FoodContext foodContext;
	SnakeMovementHandler snakeMovementHandler;
};

#endif /* SRC_GAMECONTEXT_H_ */
