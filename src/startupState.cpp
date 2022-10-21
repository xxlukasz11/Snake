#include <optional>
#include "startupState.h"

namespace {
const Position INITIAL_SNAKE_POSITION = { 20, 20 };

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
} // namespace

StartupState::StartupState(StateMachine& stateMachine, GameContext& gameContext) :
		StateBase(stateMachine),
		wolrdMap(gameContext.getWolrdMap()),
		snakeContext(gameContext.getSnakeContext()) {
}

void StartupState::onEnter() {
	snakeContext.appendHeadSegment(INITIAL_SNAKE_POSITION);
	wolrdMap.drawMap();
	wolrdMap.drawSnake(snakeContext);
	wolrdMap.flushDisplay();
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
