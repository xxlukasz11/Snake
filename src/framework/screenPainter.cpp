#include "../framework/screenPainter.h"

#include "color.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

namespace {

ALLEGRO_COLOR allegroColor(const Color& color) {
	return al_map_rgb(color.r(), color.g(), color.b());
}

} // namespace

void ScreenPainter::drawFilledRectangle(double topLeftX, double topLeftY, double bottomRightX, double bottomRightY,
		const Color& fillColor) const {
	al_draw_filled_rectangle(topLeftX, topLeftY, bottomRightX, bottomRightY, allegroColor(fillColor));
}

void ScreenPainter::drawFilledCircle(double centerX, double centerY, double radius, const Color& fillColor) const {
	al_draw_filled_circle(centerX, centerY, radius, allegroColor(fillColor));
}

void ScreenPainter::clearScreen(const Color& screenColor) const {
	al_clear_to_color(allegroColor(screenColor));
}

void ScreenPainter::flushBuffer() const {
	al_flip_display();
}
