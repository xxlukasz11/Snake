#include "snakeContext.h"

static const ALLEGRO_COLOR HEAD_COLOR = al_map_rgb(255, 0, 0);
static const ALLEGRO_COLOR BODY_COLOR = al_map_rgb(68, 136, 170);

const ALLEGRO_COLOR& SnakeContext::getHeadColor() const {
	return HEAD_COLOR;
}

const ALLEGRO_COLOR& SnakeContext::getBodyColor() const {
	return BODY_COLOR;
}

const SnakeContext::Body& SnakeContext::getBody() const {
	return body;
}

const SpeedVector& SnakeContext::getSpeed() const {
	return speed;
}

int SnakeContext::getSnakeSize() const {
	return body.size();
}

void SnakeContext::setSpeed(const SpeedVector& newSpeed) {
	speed = newSpeed;
}

void SnakeContext::appendHeadSegment(const Position& headPosition) {
	body.push_front(headPosition);
}

void SnakeContext::eraseTailSegment() {
	body.pop_back();
}
