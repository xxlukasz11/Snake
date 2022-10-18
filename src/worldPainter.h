#ifndef SRC_WORLDPAINTER_H_
#define SRC_WORLDPAINTER_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"

class WorldPainter {
public:
	WorldPainter(const Display& display, double pixelSize);
	void drawMap();
	void drawSnake(const SnakeContext& snake);
	void flushDisplay();

private:
	void drawPixel(double x, double y, const ALLEGRO_COLOR& color);

	const Display& display;
	double pixelSize;
	double borderSize;
};


#endif /* SRC_WORLDPAINTER_H_ */
