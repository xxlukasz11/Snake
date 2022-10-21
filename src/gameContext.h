#ifndef SRC_GAMECONTEXT_H_
#define SRC_GAMECONTEXT_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"
#include "worldPainter.h"

class GameContext {
public:
	GameContext(const Display& display, int rasterSize);

	int getRasterSize() const;
	const WorldPainter& getWorldPainter() const;
	const SnakeContext& getSnakeContext() const;
	SnakeContext& getSnakeContext();

private:
	int rasterSize;
	WorldPainter worldPainter;
	SnakeContext snakeContext;
	// TODO food info
};

#endif /* SRC_GAMECONTEXT_H_ */
