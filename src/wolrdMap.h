#ifndef SRC_WOLRDMAP_H_
#define SRC_WOLRDMAP_H_

#include "basic_allegro.hpp"
#include "snakeContext.h"

class WolrdMap {
public:
	WolrdMap(const Display& display, double rasterSize);
	void drawMap() const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;

	double getRasterSize() const;
	int getBorderRasters() const;

private:
	void drawRaster(double x, double y, const ALLEGRO_COLOR& color) const;

	const Display& display;
	const double rasterSize;
	const double borderSize;
};

#endif /* SRC_WOLRDMAP_H_ */
