#include "snakeContext.h"
#include <algorithm>

static const Color HEAD_COLOR = Color::rgb(255, 0, 0);
static const Color BODY_COLOR = Color::rgb(68, 136, 170);

void SnakeContext::reset() {
	body.clear();
	speed = { 0, 0 };
}

const Color& SnakeContext::getHeadColor() const {
	return HEAD_COLOR;
}

const Color& SnakeContext::getBodyColor() const {
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

bool SnakeContext::isHeadOverBodySegment() const {
	if (body.size() < 4) {
		return false;
	}

	const auto& headPos = body.cbegin();
	return std::any_of(std::next(headPos), body.cend(), [&headPos](auto&& pos) {
		return pos == *headPos;
	});
}
