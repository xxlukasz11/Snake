#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "worldMap.h"
#include "snakeContext.h"
#include "foodContext.h"

constexpr int BORDER_RASTERS = 1;
static const ALLEGRO_COLOR BORDER_COLOR = al_map_rgb(35, 121, 22);
static const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(238, 230, 165);
static const ALLEGRO_COLOR FOOD_COLOR = al_map_rgb(0, 0, 0);

WorldMap::WorldMap(const Display& display, double rasterSize) :
		display(display),
		rasterSize(rasterSize),
		borderSize(rasterSize * BORDER_RASTERS) {
}

void WorldMap::drawMap() const {
	al_clear_to_color(BORDER_COLOR);
	al_draw_filled_rectangle(borderSize, borderSize, display.width - borderSize, display.height - borderSize,
			BACKGROUND_COLOR);
}

void WorldMap::drawFood(const FoodContext& foodContext) const {
	const auto& foodPosition = foodContext.getFoodPositon();
	if (foodPosition.has_value()) {
		drawFoodAt(foodPosition.value());
	}
}

void WorldMap::drawFoodAt(const Position& position) const {
	const double circleRadius = rasterSize / 2.2;
	const auto xOffset = position.x * rasterSize + circleRadius;
	const auto yoffset = position.y * rasterSize + circleRadius;
	al_draw_filled_circle(xOffset, yoffset, circleRadius, FOOD_COLOR);
}

void WorldMap::drawSnake(const SnakeContext& snake) const {
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}

	const auto& head = body[0];
	drawRaster(head.x, head.y, snake.getHeadColor());
	for (size_t i = 1; i < body.size(); ++i) {
		const auto& segment = body[i];
		drawRaster(segment.x, segment.y, snake.getBodyColor());
	}
}

void WorldMap::drawRaster(double x, double y, const ALLEGRO_COLOR& color) const {
	const auto xOffset = x * rasterSize;
	const auto yOffset = y * rasterSize;
	al_draw_filled_rectangle(xOffset, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
}

void WorldMap::flushDisplay() const {
	al_flip_display();
}

Area WorldMap::calculateAvailableArea() const {
	int horizontalRasters = display.width / rasterSize;
	int verticalRasters = display.height / rasterSize;
	Position topLeft{ BORDER_RASTERS, BORDER_RASTERS };
	Position bottomRight{ horizontalRasters - BORDER_RASTERS, verticalRasters - BORDER_RASTERS };
	return Area{ topLeft, bottomRight };
}

double WorldMap::getRasterSize() const {
	return rasterSize;
}
