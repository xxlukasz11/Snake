#ifndef SRC_SCREENPAINTER_H_
#define SRC_SCREENPAINTER_H_

#include "utils.h"

class Color;

class ScreenPainter {
public:
	void drawFilledRectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY,
			const Color& fillColor) const;
	void drawFilledCircle(double centerX, double centerY, double radius, const Color& fillColor) const;
	void clearScreen(const Color& screenColor) const;
	void flushBuffer() const;
};

#endif /* SRC_SCREENPAINTER_H_ */
