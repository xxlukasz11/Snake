#include "worldPainter.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "snakeContext.h"
#include "foodContext.h"

constexpr int BORDER_RASTERS = 1;
static const ALLEGRO_COLOR BACKGROUND_COLOR = al_map_rgb(238, 230, 165);
static const ALLEGRO_COLOR FOOD_COLOR = al_map_rgb(0, 0, 0);

WorldPainter::WorldPainter(const Display& display) :
		display(display),
		rasterSize(display.rasterSize),
		borderSize(display.rasterSize * BORDER_RASTERS) {
}

void WorldPainter::drawMap(const WorldMapContext& worldMapContext) const {
	// TODO: make this class independent from allegro -> create primitives painter
	al_clear_to_color(BACKGROUND_COLOR);
	const auto& borderColor = worldMapContext.getBorderColor();
	for (const auto& border : worldMapContext.getBorders()) {
		const auto& area = border.getArea();
		al_draw_filled_rectangle(area.topLeft.x * rasterSize, area.topLeft.y * rasterSize,
				area.bottomRight.x * rasterSize, area.bottomRight.y * rasterSize, borderColor);
	}
}

void WorldPainter::drawFood(const FoodContext& foodContext) const {
	const auto& foodPosition = foodContext.getFoodPositon();
	if (foodPosition.has_value()) {
		drawFoodAt(foodPosition.value());
	}
}

void WorldPainter::drawFoodAt(const Position& position) const {
	const double circleRadius = rasterSize / 2.2;
	const auto xOffset = position.x * rasterSize + circleRadius;
	const auto yOffset = position.y * rasterSize + circleRadius;
	al_draw_filled_circle(xOffset, yOffset, circleRadius, FOOD_COLOR);
}

void WorldPainter::drawSnake(const SnakeContext& snake) const {
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}
	drawSnakeHead(body, snake.getHeadColor());
	drawSnakeBody(body, snake.getBodyColor());
}

void WorldPainter::drawSnakeHead(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const {
	const auto& head = bodySegments[0];
	if (bodySegments.size() > 1) {
		drawRoundedSegment(head, bodySegments[1], color);
	} else {
		drawRoundedSegment(head, head, color);
	}
}

void WorldPainter::drawSnakeBody(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const {
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

void WorldPainter::drawRoundedSegment(const Position& tailPos, const Position& adjacentSegmentPos,
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

void WorldPainter::drawBodySegment(const Position& segmentPos, const ALLEGRO_COLOR& color) const {
	const auto xOffset = segmentPos.x * rasterSize;
	const auto yOffset = segmentPos.y * rasterSize;
	al_draw_filled_rectangle(xOffset, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
}

void WorldPainter::flushDisplay() const {
	al_flip_display();
}

Area WorldPainter::calculateAvailableArea() const {
	int horizontalRasters = display.width / rasterSize;
	int verticalRasters = display.height / rasterSize;
	Position topLeft{ BORDER_RASTERS, BORDER_RASTERS };
	Position bottomRight{ horizontalRasters - BORDER_RASTERS - 1, verticalRasters - BORDER_RASTERS - 1 };
	return Area{ topLeft, bottomRight };
}

double WorldPainter::getRasterSize() const {
	return rasterSize;
}
