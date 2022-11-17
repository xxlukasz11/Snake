#include "screenPainter.h"
#include <allegro5/allegro_primitives.h>

void ScreenPainter::drawFilledRectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY,
		const ALLEGRO_COLOR& fillColor) const {
	al_draw_filled_rectangle(topLeftX, topLeftY, bottomRightX, bottomRightY, fillColor);
}

void ScreenPainter::drawFilledCircle(double centerX, double centerY, double radius,
		const ALLEGRO_COLOR& fillColor) const {
	al_draw_filled_circle(centerX, centerY, radius, fillColor);
}

void ScreenPainter::clearScreen(const ALLEGRO_COLOR& screenColor) const {
	al_clear_to_color(screenColor);
}

void ScreenPainter::flushBuffer() const {
	al_flip_display();
}
