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

void WorldPainter::draw() {
	al_clear_to_color(BORDER_COLOR);
	al_draw_filled_rectangle(borderSize, borderSize, display.width - borderSize, display.height - borderSize,
			BACKGROUND_COLOR);
	//al_draw_filled_circle(jx + part_size / 2, jy + part_size / 2, part_size / 2.2, al_map_rgb(0, 0, 0));
	//al_draw_filled_rectangle(x[0], y[0], x[0] + part_size, y[0] + part_size, head_color);
	//for (int i = 1; i < snake_size; i++) {
	//	al_draw_filled_rectangle(x[i], y[i], x[i] + part_size, y[i] + part_size, snake_color);
	//}
}
