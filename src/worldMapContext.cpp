#include "worldMapContext.h"
#include <algorithm>

static const ALLEGRO_COLOR BORDER_COLOR = al_map_rgb(35, 121, 22);

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
