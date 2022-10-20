#include "startupState.h"

#include <optional>

namespace {
std::optional<SpeedVector> tryCalculatingSpeed(int keyCode) {
	switch (keyCode) {
	case ALLEGRO_KEY_UP:
		return SpeedVector{ 0, -1 };
		break;
	case ALLEGRO_KEY_DOWN:
		return SpeedVector{ 0, 1 };
		break;
	case ALLEGRO_KEY_LEFT:
		return SpeedVector{ -1, 0 };
		break;
	case ALLEGRO_KEY_RIGHT:
		return SpeedVector{ 1, 0 };
		break;
	default:
		return std::nullopt;
	}
}
}

StartupState::StartupState(StateMachine& stateMachine, WorldPainter& painter, SnakeContext& snakeContext) :
		StateBase(stateMachine),
		painter(painter),
		snakeContext(snakeContext) {
}

void StartupState::onEnter() {
	snakeContext.appendHeadSegment({ 300, 300 });
	painter.drawMap();
	painter.drawSnake(snakeContext);
	painter.flushDisplay();
}

void StartupState::handleStateEvent(const ALLEGRO_EVENT& event) {
	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		handleKeyDown(event.keyboard.keycode);
	}
}

void StartupState::handleKeyDown(int keyCode) {
	const auto speed = tryCalculatingSpeed(keyCode);
	if (!speed.has_value()) {
		return;
	}

	snakeContext.setSpeed(speed.value());
	nextState(StateType::PLAY);
}
