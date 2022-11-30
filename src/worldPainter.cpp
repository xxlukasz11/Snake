#include <cmath>
#include "worldPainter.h"
#include "color.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "framework/display.h"

using framework::Display;

constexpr double SNAKE_BODY_OFFSET = 3.0;
constexpr double FOOD_RADIUS_FACTOR = 0.3;
static const Color BACKGROUND_COLOR = Color::rgb(238, 230, 165);
static const Color FOOD_COLOR = Color::rgb(0, 0, 0);

namespace {

bool areSegmentsInLine(const Vector2D& firstSegment, const Vector2D& secondSegment) {
	return firstSegment.x == secondSegment.x || firstSegment.y == secondSegment.y;
}

Vector2D calculateVector(const Vector2D& from, const Vector2D& to) {
	return {to.x - from.x, to.y - from.y};
}

/*
 * Calculate vector pointing inside snake body bend
 */
Vector2D calculateBendVector(const Vector2D& prevPos, const Vector2D& middlePos, const Vector2D& nextPos) {
	auto prevDir = calculateVector(middlePos, prevPos);
	auto nextDir = calculateVector(middlePos, nextPos);
	return {prevDir.x + nextDir.x, prevDir.y + nextDir.y};
}

/*
 * Calculate starting angle for the arc at the snake body bend
 */
double calculateInitialTheta(const Vector2D& bendVector) {
	if (bendVector.x > 0 && bendVector.y < 0) {
		// Top-right bend
		return M_PI_2;
	} else if (bendVector.x > 0 && bendVector.y > 0) {
		// Bottom-right bend
		return M_PI;
	} else if (bendVector.x < 0 && bendVector.y > 0) {
		// Bottom-left bend
		return M_PI + M_PI_2;
	}
	// Top-left bend
	return 0.0;
}

} // namespace

WorldPainter::WorldPainter(const Display& display) :
		display(display),
		rasterSize(display.getRasterSize()),
		snakeWidth(rasterSize - 2 * SNAKE_BODY_OFFSET),
		foodRadius(rasterSize * FOOD_RADIUS_FACTOR),
		screenPainter() {
}

void WorldPainter::drawMap(const WorldMapContext& worldMapContext) const {
	screenPainter.clearScreen(BACKGROUND_COLOR);
	const auto& borderColor = worldMapContext.getBorderColor();
	for (const auto& border : worldMapContext.getBorders()) {
		const auto& area = border.getArea();
		screenPainter.drawFilledRectangle(area.topLeft.x * rasterSize, area.topLeft.y * rasterSize,
				area.bottomRight.x * rasterSize, area.bottomRight.y * rasterSize, borderColor);
	}
}

void WorldPainter::drawFood(const FoodContext& foodContext) const {
	const auto& foodPosition = foodContext.getFoodPositon();
	if (foodPosition.has_value()) {
		drawFoodAt(foodPosition.value());
	}
}

void WorldPainter::drawFoodAt(const Vector2D& position) const {
	const auto xOffset = position.x * rasterSize + foodRadius;
	const auto yOffset = position.y * rasterSize + foodRadius;
	screenPainter.drawFilledCircle(xOffset, yOffset, foodRadius, FOOD_COLOR);
}

void WorldPainter::drawSnake(const SnakeContext& snake) const {
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}
	drawSnakeBody(body, snake.getBodyColor());
	drawSnakeHead(body, snake.getHeadColor());
}

void WorldPainter::drawSnakeHead(const SnakeContext::Body bodySegments, const Color& color) const {
	const auto& head = bodySegments[0];
	if (bodySegments.size() > 1) {
		drawRoundedSegment(head, bodySegments[1], color);
	} else {
		drawRoundedSegment(head, head, color);
	}
}

void WorldPainter::drawSnakeBody(const SnakeContext::Body bodySegments, const Color& color) const {
	const auto bodySize = bodySegments.size();
	for (size_t i = 1; i < bodySize; ++i) {
		const auto& segment = bodySegments[i];
		if (i == bodySize - 1) {
			drawRoundedSegment(segment, bodySegments[i - 1], color);
		} else if (areSegmentsInLine(bodySegments[i - 1], bodySegments[i + 1])) {
			drawBodySegment(segment, bodySegments[i + 1], color);
		} else {
			drawBendSegment(segment, bodySegments[i - 1], bodySegments[i + 1], color);
		}
	}
}

void WorldPainter::drawRoundedSegment(const Vector2D& segmentPos, const Vector2D& adjacentSegmentPos,
		const Color& color) const {
	const auto xOffset = segmentPos.x * rasterSize;
	const auto yOffset = segmentPos.y * rasterSize;
	const auto radius = snakeWidth / 2.0;
	const auto xCenter = xOffset + rasterSize / 2.0;
	const auto yCenter = yOffset + rasterSize / 2.0;
	const auto yBodyOffset = yOffset + SNAKE_BODY_OFFSET;
	const auto xBodyOffset = xOffset + SNAKE_BODY_OFFSET;

	const auto direction = calculateVector(segmentPos, adjacentSegmentPos);
	if (direction.x > 0) {
		screenPainter.drawFilledRectangle(xCenter, yBodyOffset, xOffset + rasterSize, yBodyOffset + snakeWidth, color);
	} else if (direction.x < 0) {
		screenPainter.drawFilledRectangle(xOffset, yBodyOffset, xCenter, yBodyOffset + snakeWidth, color);
	} else if (direction.y > 0) {
		screenPainter.drawFilledRectangle(xBodyOffset, yCenter, xBodyOffset + snakeWidth, yOffset + rasterSize, color);
	} else if (direction.y < 0) {
		screenPainter.drawFilledRectangle(xBodyOffset, yOffset, xBodyOffset + snakeWidth, yCenter, color);
	}
	screenPainter.drawFilledCircle(xCenter, yCenter, radius, color);
}

void WorldPainter::drawBendSegment(const Vector2D& segmentPos, const Vector2D& previousSegmentPos,
		const Vector2D& nextSegmentPos, const Color& color) const {
	const auto bendVector = calculateBendVector(previousSegmentPos, segmentPos, nextSegmentPos);
	const auto initialTheta = calculateInitialTheta(bendVector);
	const auto radius = rasterSize / 2.0;
	const auto arcThickness = snakeWidth;

	auto arcCenter = segmentPos;
	arcCenter.x += (bendVector.x > 0);
	arcCenter.y += (bendVector.y > 0);

	screenPainter.drawArc(arcCenter.x * rasterSize, arcCenter.y * rasterSize, radius, initialTheta, M_PI_2,
			arcThickness, color);
}

void WorldPainter::drawBodySegment(const Vector2D& segmentPos, const Vector2D& adjacentSegmentPos,
		const Color& color) const {
	const auto direction = calculateVector(segmentPos, adjacentSegmentPos);
	const auto xOffset = segmentPos.x * rasterSize;
	const auto yOffset = segmentPos.y * rasterSize;
	if (direction.x != 0) {
		const auto yBodyOffset = yOffset + SNAKE_BODY_OFFSET;
		screenPainter.drawFilledRectangle(xOffset, yBodyOffset, xOffset + rasterSize, yBodyOffset + snakeWidth, color);
	} else {
		const auto xBodyOffset = xOffset + SNAKE_BODY_OFFSET;
		screenPainter.drawFilledRectangle(xBodyOffset, yOffset, xBodyOffset + snakeWidth, yOffset + rasterSize, color);
	}
}

void WorldPainter::flushDisplay() const {
	screenPainter.flushBuffer();
}

double WorldPainter::getRasterSize() const {
	return rasterSize;
}
