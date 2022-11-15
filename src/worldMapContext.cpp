#include "worldMapContext.h"
#include <algorithm>

static const ALLEGRO_COLOR DEFAULT_BORDER_COLOR = al_map_rgb(35, 121, 22);

const std::vector<Border>& WorldMapContext::getBorders() const {
	return borders;
}
bool WorldMapContext::isBorderHere(const Position& position) const {
	return std::any_of(borders.cbegin(), borders.cend(), [&position](auto&& border) {
		return border.isPartOfTheBorder(position);
	});
}

const ALLEGRO_COLOR& WorldMapContext::getBorderColor() const {
	return borderColor;
}

WorldMapContext::Builder::Builder() :
		borderColor(DEFAULT_BORDER_COLOR) {
}

WorldMapContext::Builder WorldMapContext::Builder::instance() {
	return Builder{ };

}

WorldMapContext::Builder& WorldMapContext::Builder::addBorder(const Border& border) {
	this->borders.push_back(border);
	return *this;
}

WorldMapContext::Builder& WorldMapContext::Builder::setBorderColor(const ALLEGRO_COLOR& borderColor) {
	this->borderColor = borderColor;
	return *this;
}

WorldMapContext WorldMapContext::Builder::build() const {
	auto worldMap = WorldMapContext{ };
	worldMap.borders = borders;
	worldMap.borderColor = borderColor;
	return worldMap;
}
