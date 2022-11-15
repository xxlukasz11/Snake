#include "positionGenerator.h"

PositionGenerator::PositionGenerator(const Area& area) :
		generator(std::random_device{ }()),
		xDistrib(area.topLeft.x, area.bottomRight.x),
		yDistrib(area.topLeft.y, area.bottomRight.y) {
}

int PositionGenerator::randomX() {
	return xDistrib(generator);
}

int PositionGenerator::randomY() {
	return yDistrib(generator);
}
