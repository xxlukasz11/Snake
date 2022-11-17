#ifndef SRC_SCREENPAINTER_H_
#define SRC_SCREENPAINTER_H_

#include "utils.h"
#include <allegro5/allegro_color.h>

class ScreenPainter {
public:
	void drawFilledRectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY,
			const ALLEGRO_COLOR& fillColor) const;
	void drawFilledCircle(double centerX, double centerY, double radius, const ALLEGRO_COLOR& fillColor) const;
	void clearScreen(const ALLEGRO_COLOR& screenColor) const;
	void flushBuffer() const;
};

#endif /* SRC_SCREENPAINTER_H_ */
