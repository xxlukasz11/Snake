#ifndef SRC_WORLDPAINTER_H_
#define SRC_WORLDPAINTER_H_

#include "display.h"
#include "snakeContext.h"
#include "worldMapContext.h"
#include "utils.h"
#include "screenPainter.h"

class FoodContext;

class WorldPainter {
public:
	WorldPainter(const Display& display);
	void drawMap(const WorldMapContext& worldMapContext) const;
	void drawFood(const FoodContext& foodContext) const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;
	double getRasterSize() const;

private:
	void drawFoodAt(const Position& position) const;
	void drawSnakeHead(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const;
	void drawSnakeBody(const SnakeContext::Body bodySegments, const ALLEGRO_COLOR& color) const;
	void drawRoundedSegment(const Position& tailPos, const Position& adjacentSegmentPos,
			const ALLEGRO_COLOR& color) const;
	void drawBodySegment(const Position& segmentPos, const ALLEGRO_COLOR& color) const;

	const Display& display;
	const double rasterSize;
	ScreenPainter screenPainter;
};

#endif /* SRC_WORLDPAINTER_H_ */
