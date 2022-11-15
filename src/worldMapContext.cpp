#include "worldMapContext.h"
#include <algorithm>

static const ALLEGRO_COLOR DEFAULT_BORDER_COLOR = al_map_rgb(35, 121, 22);
static const Area DEFAULT_FOOD_AREA = Area{ { 0, 0 }, { 1, 1 } };

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

const Area& WorldMapContext::getFoodArea() const {
	return foodArea;
}

WorldMapContext::Builder::Builder() :
		borderColor(DEFAULT_BORDER_COLOR),
		foodArea(DEFAULT_FOOD_AREA) {
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

WorldMapContext::Builder& WorldMapContext::Builder::setFoodArea(const Area& foodArea) {
	this->foodArea = foodArea;
	return *this;
}

WorldMapContext WorldMapContext::Builder::build() const {
	auto worldMap = WorldMapContext{ };
	worldMap.borders = borders;
	worldMap.borderColor = borderColor;
	worldMap.foodArea = foodArea;
	return worldMap;
}
