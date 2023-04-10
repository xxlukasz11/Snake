#ifndef SRC_WORLDMAPFRAMEBUILDER_H_
#define SRC_WORLDMAPFRAMEBUILDER_H_

#include "worldMapContext.h"
#include "utils.h"
#include "allegro-cpp/color.h"

class WorldMapFrameBuilder {
public:
	static WorldMapFrameBuilder instance(const Area& frameArea);
	WorldMapFrameBuilder& setFrameThickness(int frameThickness);
	WorldMapFrameBuilder& setFrameColor(const allegrocpp::Color& frameColor);
	WorldMapContext build() const;

private:
	WorldMapFrameBuilder(const Area& frameArea);
	WorldMapContext::Builder constructFrame() const;
	Area calculateFoodArea() const;

	Area frameArea;
	int frameThickness;
	allegrocpp::Color frameColor;
};

#endif /* SRC_WORLDMAPFRAMEBUILDER_H_ */
