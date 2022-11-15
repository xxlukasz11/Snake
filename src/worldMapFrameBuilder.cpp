#include "worldMapFrameBuilder.h"

constexpr int DEFAULT_FRAME_THICKNESS = 1;
static const ALLEGRO_COLOR DEFAULT_FRAME_COLOR = al_map_rgb(35, 121, 22);

WorldMapFrameBuilder WorldMapFrameBuilder::instance(const Area& frameArea) {
	return WorldMapFrameBuilder{ frameArea };
}

WorldMapFrameBuilder& WorldMapFrameBuilder::setFrameThickness(int frameThickness) {
	this->frameThickness = frameThickness;
	return *this;
}

WorldMapFrameBuilder& WorldMapFrameBuilder::setFrameColor(const ALLEGRO_COLOR& frameColor) {
	this->frameColor = frameColor;
	return *this;
}

WorldMapContext WorldMapFrameBuilder::build() const {
	auto builder = constructFrame();
	builder.setBorderColor(frameColor);
	builder.setFoodArea(calculateFoodArea());
	return builder.build();
}

WorldMapFrameBuilder::WorldMapFrameBuilder(const Area& frameArea) :
		frameArea(frameArea),
		frameThickness(DEFAULT_FRAME_THICKNESS),
		frameColor(DEFAULT_FRAME_COLOR) {
}

WorldMapContext::Builder WorldMapFrameBuilder::constructFrame() const {
	auto minX = frameArea.topLeft.x;
	auto minY = frameArea.topLeft.y;
	auto maxX = frameArea.bottomRight.x;
	auto maxY = frameArea.bottomRight.y;
	auto builder = WorldMapContext::Builder::instance();

	Border top = Area{ frameArea.topLeft, { maxX, frameThickness } };
	builder.addBorder(top);

	Border bottom = Area{ { minX, maxY - frameThickness }, { maxX, maxY } };
	builder.addBorder(bottom);

	Border left = Area{ { minX, minY + frameThickness }, { frameThickness, maxY - frameThickness } };
	builder.addBorder(left);

	Border right = Area{ { maxX - frameThickness, minY + frameThickness }, { maxX, maxY - frameThickness } };
	builder.addBorder(right);

	return builder;
}

Area WorldMapFrameBuilder::calculateFoodArea() const {
	Position innerTopLeft = { frameArea.topLeft.x + frameThickness, frameArea.topLeft.y + frameThickness };
	Position innerBottomRight = { frameArea.bottomRight.x - frameThickness, frameArea.bottomRight.y - frameThickness };
	Area foodArea = { innerTopLeft, innerBottomRight };
	return foodArea;
}
