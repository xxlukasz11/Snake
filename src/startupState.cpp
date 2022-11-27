#include <optional>
#include "startupState.h"

using framework::Event;
using framework::KeyboardKey;

namespace {

std::optional<SpeedVector> tryCalculatingSpeed(const Event& event) {
	if (event.isKeyPressed(KeyboardKey::KEY_UP)) {
		return SpeedVector{ 0, -1 };
	}
	if (event.isKeyPressed(KeyboardKey::KEY_DOWN)) {
		return SpeedVector{ 0, 1 };
	}
	if (event.isKeyPressed(KeyboardKey::KEY_LEFT)) {
		return SpeedVector{ -1, 0 };
	}
	if (event.isKeyPressed(KeyboardKey::KEY_RIGHT)) {
		return SpeedVector{ 1, 0 };
	}
	return std::nullopt;
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
	auto& writer = appContext.getTextWriter();
	writer.writeCenter("Press any arrow to start the game");
}

void StartupState::handleStateEvent(const Event& event) {
	const auto speed = tryCalculatingSpeed(event);
	if (!speed.has_value()) {
		return;
	}

	snakeContext.setSpeed(speed.value());
	nextState(StateType::PLAY);
}
