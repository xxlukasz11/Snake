#include "worldMapContext.h"
#include <algorithm>

static const ALLEGRO_COLOR BORDER_COLOR = al_map_rgb(35, 121, 22);
constexpr int WIDTH = 54;
constexpr int HEIGHT = 34;
constexpr int BORDER_WIDTH = 1;
static const Border TOP = Area{ { 0, 0 }, { WIDTH, BORDER_WIDTH } };
static const Border BOTTOM = Area{ { 0, HEIGHT - BORDER_WIDTH }, { WIDTH, HEIGHT } };
static const Border LEFT = Area{ { 0, BORDER_WIDTH }, { BORDER_WIDTH, HEIGHT - BORDER_WIDTH } };
static const Border RIGHT = Area{ { WIDTH - BORDER_WIDTH, BORDER_WIDTH }, { WIDTH, HEIGHT - BORDER_WIDTH } };

WorldMapContext::WorldMapContext() :
		// TODO: Implement WorldMapBuilder
		borders({ TOP, BOTTOM, LEFT, RIGHT }) {
}

const std::vector<Border>& WorldMapContext::getBorders() const {
	return borders;
}
bool WorldMapContext::isBorderHere(const Position& position) const {
	return std::any_of(borders.cbegin(), borders.cend(), [&position](auto&& border) {
		return border.isPartOfTheBorder(position);
	});
}

const ALLEGRO_COLOR& WorldMapContext::getBorderColor() const {
	return BORDER_COLOR;
}
