#ifndef SRC_WORLDMAPPAINTER_H_
#define SRC_WORLDMAPPAINTER_H_

#include "basic_allegro.h"
#include "snakeContext.h"
#include "worldMapContext.h"
#include "utils.h"

class FoodContext;

class WorldMapPainter {
public:
	WorldMapPainter(const Display& display, double rasterSize);
	void drawMap(const WorldMapContext& worldMapContext) const;
	void drawFood(const FoodContext& foodContext) const;
	void drawSnake(const SnakeContext& snake) const;
	void flushDisplay() const;
	Area calculateAvailableArea() const;
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
	const double borderSize;
};

#endif /* SRC_WORLDMAPPAINTER_H_ */
