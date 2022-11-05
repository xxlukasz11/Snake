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
	// TODO: split world map and painter contexts
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
	const auto yOffset = position.y * rasterSize + circleRadius;
	al_draw_filled_circle(xOffset, yOffset, circleRadius, FOOD_COLOR);
}

void WorldMap::drawSnake(const SnakeContext& snake) const {
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}
	drawSnakeHead(body, snake.getHeadColor());
	drawSnakeBody(body, snake.getBodyColor());
}

void WorldMap::drawSnakeHead(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const {
	const auto& head = bodySegments[0];
	if (bodySegments.size() > 1) {
		drawRoundedSegment(head, bodySegments[1], color);
	} else {
		drawRoundedSegment(head, head, color);
	}
}

void WorldMap::drawSnakeBody(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const {
	const auto bodySize = bodySegments.size();
	for (size_t i = 1; i < bodySize; ++i) {
		const auto& segment = bodySegments[i];
		if (i == bodySize - 1) {
			drawRoundedSegment(segment, bodySegments[i - 1], color);
		} else {
			drawBodySegment(segment, color);
		}
	}
}

void WorldMap::drawRoundedSegment(const Position& tailPos, const Position& adjacentSegmentPos,
		const ALLEGRO_COLOR& color) const {
	const auto xOffset = tailPos.x * rasterSize;
	const auto yOffset = tailPos.y * rasterSize;
	const auto radius = rasterSize / 2;
	const auto xCenter = xOffset + radius;
	const auto yCenter = yOffset + radius;

	const auto direction = SpeedVector{ adjacentSegmentPos.x - tailPos.x, adjacentSegmentPos.y - tailPos.y };
	if (direction.x > 0) {
		al_draw_filled_rectangle(xCenter, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
	} else if (direction.x < 0) {
		al_draw_filled_rectangle(xOffset, yOffset, xCenter, yOffset + rasterSize, color);
	} else if (direction.y > 0) {
		al_draw_filled_rectangle(xOffset, yCenter, xOffset + rasterSize, yOffset + rasterSize, color);
	} else if (direction.y < 0) {
		al_draw_filled_rectangle(xOffset, yOffset, xOffset + rasterSize, yCenter, color);
	}
	al_draw_filled_circle(xCenter, yCenter, radius, color);
}

void WorldMap::drawBodySegment(const Position& segmentPos, const ALLEGRO_COLOR& color) const {
	const auto xOffset = segmentPos.x * rasterSize;
	const auto yOffset = segmentPos.y * rasterSize;
	al_draw_filled_rectangle(xOffset, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
}

void WorldMap::flushDisplay() const {
	al_flip_display();
}

Area WorldMap::calculateAvailableArea() const {
	int horizontalRasters = display.width / rasterSize;
	int verticalRasters = display.height / rasterSize;
	Position topLeft{ BORDER_RASTERS, BORDER_RASTERS };
	Position bottomRight{ horizontalRasters - BORDER_RASTERS - 1, verticalRasters - BORDER_RASTERS - 1 };
	return Area{ topLeft, bottomRight };
}

double WorldMap::getRasterSize() const {
	return rasterSize;
}

bool WorldMap::isBorderHere(const Position& position) const {
	// TODO: create generic border representation, so that it is possible to create complex maps
	const int horizontalRasters = display.width / rasterSize;
	if (position.x < BORDER_RASTERS || position.x >= horizontalRasters - BORDER_RASTERS) {
		return true;
	}

	const int verticalRasters = display.height / rasterSize;
	if (position.y < BORDER_RASTERS || position.y >= verticalRasters - BORDER_RASTERS) {
		return true;
	}
	return false;
}
