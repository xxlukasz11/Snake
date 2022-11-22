#include <optional>
#include "framework/textWriter.h"
#include "startupState.h"

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
} // namespace

StartupState::StartupState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		painter(gameContext.getPainter()),
		snakeContext(gameContext.getSnakeContext()),
		gameContext(gameContext) {
}

void StartupState::onEnter() {
	initializeSnakeBody();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawSnake(snakeContext);
	writeInstructions();
	painter.flushDisplay();
}

void StartupState::initializeSnakeBody() {
	const auto& display = appContext.getDisplay();
	Position centerPosition{ display.getWidthRasters() / 2, static_cast<int>(display.getHeightRasters() / 1.5) };
	snakeContext.appendHeadSegment(centerPosition);
}

void StartupState::writeInstructions() const {
	framework::TextWriter writer(appContext.getDisplay(), appContext.getMainFont());
	writer.writeCenter("Press any arrow to start the game");
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
