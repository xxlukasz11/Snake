#ifndef SRC_WORLDPAINTER_H_
#define SRC_WORLDPAINTER_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"

class WorldPainter {
public:
	WorldPainter(const Display& display, double rasterSize);
	void drawMap() const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;

	double getRasterSize() const;

private:
	void drawRaster(double x, double y, const ALLEGRO_COLOR& color) const;

	const Display& display;
	const double rasterSize;
	const double borderSize;
};

#endif /* SRC_WORLDPAINTER_H_ */
