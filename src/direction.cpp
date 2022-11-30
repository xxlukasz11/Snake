#include "direction.h"

Direction::Direction(const Vector2D& speedVector) :
		speedVector(speedVector) {
}

bool Direction::isOppositeTo(const Direction& direction) {
	Vector2D oppositeVector{ -speedVector.x, -speedVector.y };
	return oppositeVector == direction.speedVector;
}

Vector2D Direction::getSpeedVector() const {
	return speedVector;
}

Direction Direction::UP{ { 0, -1 } };
Direction Direction::DOWN{ { 0, 1 } };
Direction Direction::LEFT{ { -1, 0 } };
Direction Direction::RIGHT{ { 1, 0 } };
Direction Direction::NONE{ { 0, 0 } };
