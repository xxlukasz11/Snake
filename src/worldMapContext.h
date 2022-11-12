#ifndef SRC_WORLDMAPCONTEXT_H_
#define SRC_WORLDMAPCONTEXT_H_

#include <vector>
#include <allegro5/allegro_color.h>
#include "border.h"
#include "utils.h"

class WorldMapContext {
public:
	WorldMapContext();
	const std::vector<Border>& getBorders() const;
	bool isBorderHere(const Position& position) const;
	const ALLEGRO_COLOR& getBorderColor() const;

private:
	std::vector<Border> borders;
};

#endif /* SRC_WORLDMAPCONTEXT_H_ */
