#include "snakeContext.h"
#include <algorithm>

static const Color HEAD_COLOR = Color::rgb(255, 0, 0);
static const Color BODY_COLOR = Color::rgb(68, 136, 170);

void SnakeContext::reset() {
	body.clear();
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

int SnakeContext::getSnakeSize() const {
	return body.size();
}

void SnakeContext::appendHeadSegment(const Position& headPosition) {
	body.push_front(headPosition);
}

void SnakeContext::eraseTailSegment() {
	body.pop_back();
}

void SnakeContext::cutOffTailIfHeadCollided() {
	if (body.size() < 4) {
		return;
	}

	const auto& headPos = body.cbegin();
	auto found = std::find_if(std::next(headPos), body.cend(), [&headPos](auto&& pos) {
		return pos == *headPos;
	});

	if (found == body.cend()) {
		return;
	}

	body.resize(std::distance(body.cbegin(), found));
}
