#ifndef SRC_WORLDMAPCONTEXT_H_
#define SRC_WORLDMAPCONTEXT_H_

#include <vector>
#include <allegro5/allegro_color.h>
#include "border.h"
#include "utils.h"

class WorldMapContext {
public:
	const std::vector<Border>& getBorders() const;
	bool isBorderHere(const Position& position) const;
	const ALLEGRO_COLOR& getBorderColor() const;
	const Area& getFoodArea() const;

	class Builder {
	public:
		static Builder instance();
		Builder& addBorder(const Border& border);
		Builder& setBorderColor(const ALLEGRO_COLOR& borderColor);
		Builder& setFoodArea(const Area& foodArea);
		WorldMapContext build() const;

	private:
		Builder();
		std::vector<Border> borders;
		ALLEGRO_COLOR borderColor;
		Area foodArea;
	};

private:
	WorldMapContext() = default;
	std::vector<Border> borders;
	ALLEGRO_COLOR borderColor;
	Area foodArea;
};

#endif /* SRC_WORLDMAPCONTEXT_H_ */
