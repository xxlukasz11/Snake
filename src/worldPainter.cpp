#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "worldPainter.h"

static const ALLEGRO_COLOR BORDER_COLOR = al_map_rgb(35, 121, 22);
static const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(238, 230, 165);

WorldPainter::WorldPainter(const Display& display, double pixelSize) :
		display(display),
		pixelSize(pixelSize),
		borderSize(pixelSize) {
}

void WorldPainter::drawMap() {
	al_clear_to_color(BORDER_COLOR);
	al_draw_filled_rectangle(borderSize, borderSize, display.width - borderSize, display.height - borderSize,
			BACKGROUND_COLOR);
	//al_draw_filled_circle(jx + part_size / 2, jy + part_size / 2, part_size / 2.2, al_map_rgb(0, 0, 0));
	//al_draw_filled_rectangle(x[0], y[0], x[0] + part_size, y[0] + part_size, head_color);
	//for (int i = 1; i < snake_size; i++) {
	//	al_draw_filled_rectangle(x[i], y[i], x[i] + part_size, y[i] + part_size, snake_color);
	//}
}

void WorldPainter::drawSnake(const SnakeContext& snake) {
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}

	const auto& head = body[0];
	drawPixel(head.x, head.y, snake.getHeadColor());
	for (size_t i = 1; i < body.size(); ++i) {
		const auto& segment = body[i];
		drawPixel(segment.x, segment.y, snake.getBodyColor());
	}
}

void WorldPainter::drawPixel(double x, double y, const ALLEGRO_COLOR& color) {
	al_draw_filled_rectangle(x, y, x + pixelSize, y + pixelSize, color);
}

void WorldPainter::flushDisplay() {
	al_flip_display();
}

double WorldPainter::getPixelSize() const {
	return pixelSize;
}
