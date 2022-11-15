#ifndef SRC_WORLDMAPFRAMEBUILDER_H_
#define SRC_WORLDMAPFRAMEBUILDER_H_

#include <allegro5/allegro_color.h>
#include "worldMapContext.h"
#include "utils.h"

class WorldMapFrameBuilder {
public:
	static WorldMapFrameBuilder instance(const Area& frameArea);
	WorldMapFrameBuilder& setFrameThickness(int frameThickness);
	WorldMapFrameBuilder& setFrameColor(const ALLEGRO_COLOR& frameColor);
	WorldMapContext build() const;

private:
	WorldMapFrameBuilder(const Area& frameArea);
	WorldMapContext::Builder constructFrame() const;
	Area calculateFoodArea() const;

	Area frameArea;
	int frameThickness;
	ALLEGRO_COLOR frameColor;
};

#endif /* SRC_WORLDMAPFRAMEBUILDER_H_ */
