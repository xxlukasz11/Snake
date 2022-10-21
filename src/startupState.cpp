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

StartupState::StartupState(StateMachine& stateMachine, GameContext& gameContext) :
		StateBase(stateMachine),
		painter(gameContext.getWorldPainter()),
		snakeContext(gameContext.getSnakeContext()) {
}

void StartupState::onEnter() {
	snakeContext.appendHeadSegment({ 10, 10 });
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
