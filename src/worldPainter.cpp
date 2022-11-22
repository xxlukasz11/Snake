#include <cmath>
#include "worldPainter.h"
#include "color.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "framework/display.h"

using framework::Display;

static const Color BACKGROUND_COLOR = Color::rgb(238, 230, 165);
static const Color FOOD_COLOR = Color::rgb(0, 0, 0);

namespace {

bool areSegmentsInLine(const Position& firstSegment, const Position& secondSegment) {
	return firstSegment.x == secondSegment.x || firstSegment.y == secondSegment.y;
}

SpeedVector calculateVector(const Position& from, const Position& to) {
	return {to.x - from.x, to.y - from.y};
}

/*
 * Calculate vector pointing inside snake body bend
 */
SpeedVector calculateBendVector(const Position& prevPos, const Position& middlePos, const Position& nextPos) {
	auto prevDir = calculateVector(middlePos, prevPos);
	auto nextDir = calculateVector(middlePos, nextPos);
	return {prevDir.x + nextDir.x, prevDir.y + nextDir.y};
}

/*
 * Calculate starting angle for the arc at the snake body bend
 */
double calculateInitialTheta(const SpeedVector& bendVector) {
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

void WorldPainter::drawFoodAt(const Position& position) const {
	const double circleRadius = rasterSize / 2.2;
	const auto xOffset = position.x * rasterSize + circleRadius;
	const auto yOffset = position.y * rasterSize + circleRadius;
	screenPainter.drawFilledCircle(xOffset, yOffset, circleRadius, FOOD_COLOR);
}

void WorldPainter::drawSnake(const SnakeContext& snake) const {
	// TODO: make snake body a little bit more narrow
	const auto& body = snake.getBody();
	if (body.empty()) {
		return;
	}
	drawSnakeHead(body, snake.getHeadColor());
	drawSnakeBody(body, snake.getBodyColor());
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
			drawBodySegment(segment, color);
		} else {
			drawBendSegment(segment, bodySegments[i - 1], bodySegments[i + 1], color);
		}
	}
}

void WorldPainter::drawRoundedSegment(const Position& tailPos, const Position& adjacentSegmentPos,
		const Color& color) const {
	const auto xOffset = tailPos.x * rasterSize;
	const auto yOffset = tailPos.y * rasterSize;
	const auto radius = rasterSize / 2;
	const auto xCenter = xOffset + radius;
	const auto yCenter = yOffset + radius;

	const auto direction = calculateVector(tailPos, adjacentSegmentPos);
	if (direction.x > 0) {
		screenPainter.drawFilledRectangle(xCenter, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
	} else if (direction.x < 0) {
		screenPainter.drawFilledRectangle(xOffset, yOffset, xCenter, yOffset + rasterSize, color);
	} else if (direction.y > 0) {
		screenPainter.drawFilledRectangle(xOffset, yCenter, xOffset + rasterSize, yOffset + rasterSize, color);
	} else if (direction.y < 0) {
		screenPainter.drawFilledRectangle(xOffset, yOffset, xOffset + rasterSize, yCenter, color);
	}
	screenPainter.drawFilledCircle(xCenter, yCenter, radius, color);
}

void WorldPainter::drawBendSegment(const Position& segmentPos, const Position& previousSegmentPos,
		const Position& nextSegmentPos, const Color& color) const {
	auto bendVector = calculateBendVector(previousSegmentPos, segmentPos, nextSegmentPos);
	auto initialTheta = calculateInitialTheta(bendVector);

	auto arcCenter = segmentPos;
	arcCenter.x += (bendVector.x > 0);
	arcCenter.y += (bendVector.y > 0);

	screenPainter.drawFilledCircle(arcCenter.x * rasterSize, arcCenter.y * rasterSize, rasterSize, initialTheta, M_PI_2,
			color);
}

void WorldPainter::drawBodySegment(const Position& segmentPos, const Color& color) const {
	const auto xOffset = segmentPos.x * rasterSize;
	const auto yOffset = segmentPos.y * rasterSize;
	screenPainter.drawFilledRectangle(xOffset, yOffset, xOffset + rasterSize, yOffset + rasterSize, color);
}

void WorldPainter::flushDisplay() const {
	screenPainter.flushBuffer();
}

double WorldPainter::getRasterSize() const {
	return rasterSize;
}
