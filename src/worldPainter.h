#ifndef SRC_WORLDPAINTER_H_
#define SRC_WORLDPAINTER_H_

#include "basic_allegro.hpp"

class WorldPainter {
public:
	WorldPainter(const Display& display, double pixelSize);
	void draw();

private:
	const Display& display;
	double pixelSize;
	double borderSize;
};


#endif /* SRC_WORLDPAINTER_H_ */
