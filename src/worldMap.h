#ifndef SRC_WORLDMAP_H_
#define SRC_WORLDMAP_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"
#include "utils.h"

class WorldMap {
public:
	WorldMap(const Display& display, double rasterSize);
	void drawMap() const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;
	Area calculateAvailableArea() const;
	double getRasterSize() const;

private:
	void drawRaster(double x, double y, const ALLEGRO_COLOR& color) const;

	const Display& display;
	const double rasterSize;
	const double borderSize;
};

#endif /* SRC_WORLDMAP_H_ */
