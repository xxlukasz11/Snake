#ifndef SRC_WORLDPAINTER_H_
#define SRC_WORLDPAINTER_H_

#include "allegro-cpp/screenPainter.h"
#include "snakeContext.h"
#include "worldMapContext.h"
#include "utils.h"

namespace allegrocpp {
class Display;
class Color;
}

class FoodContext;

class WorldPainter {
public:
	WorldPainter(const allegrocpp::Display& display);
	void drawMap(const WorldMapContext& worldMapContext) const;
	void drawFood(const FoodContext& foodContext) const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;
	double getRasterSize() const;

private:
	void drawFoodAt(const Vector2D& position) const;
	void drawSnakeHead(const SnakeContext::Body bodySegments, const allegrocpp::Color& color) const;
	void drawSnakeBody(const SnakeContext::Body bodySegments, const allegrocpp::Color& color) const;
	void drawRoundedSegment(const Vector2D& tailPos, const Vector2D& adjacentSegmentPos,
			const allegrocpp::Color& color) const;
	void drawBendSegment(const Vector2D& segmentPos, const Vector2D& previousSegmentPos, const Vector2D& nextSegmentPos,
			const allegrocpp::Color& color) const;
	void drawBodySegment(const Vector2D& segmentPos, const Vector2D& adjacentSegmentPos,
			const allegrocpp::Color& color) const;

	const allegrocpp::Display& display;
	const double rasterSize;
	const double snakeWidth;
	const double foodRadius;
	allegrocpp::ScreenPainter screenPainter;
};

#endif /* SRC_WORLDPAINTER_H_ */
