#include "border.h"

Border::Border(const Area& area) :
		area(area) {
}

bool Border::isPartOfTheBorder(const Vector2D& position) const {
	return position.x >= area.topLeft.x && position.x < area.bottomRight.x && position.y >= area.topLeft.y
			&& position.y < area.bottomRight.y;
}

const Area& Border::getArea() const {
	return area;
}
