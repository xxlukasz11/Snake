#include <optional>
#include "startupState.h"

using framework::Event;
using framework::KeyboardKey;

namespace {

std::optional<Vector2D> tryCalculatingSpeed(const KeyboardKey& key) {
	if (KeyboardKey::KEY_UP == key) {
		return Vector2D{ 0, -1 };
	}
	if (KeyboardKey::KEY_DOWN == key) {
		return Vector2D{ 0, 1 };
	}
	if (KeyboardKey::KEY_LEFT == key) {
		return Vector2D{ -1, 0 };
	}
	if (KeyboardKey::KEY_RIGHT == key) {
		return Vector2D{ 1, 0 };
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
	Vector2D centerPosition{ display.getWidthRasters() / 2, static_cast<int>(display.getHeightRasters() / 1.5) };
	snakeContext.appendHeadSegment(centerPosition);
}

void StartupState::writeInstructions() const {
	auto& writer = appContext.getTextWriter();
	writer.writeCenter("Press any arrow to start the game");
}

void StartupState::handleStateEvent(const Event& event) {
	if (!event.isKeyPressed()) {
		return;
	}

	const auto speed = tryCalculatingSpeed(event.getKey());
	if (!speed.has_value()) {
		return;
	}

	setInitialSnakeSpeed(speed.value());
	nextState(StateType::PLAY);
}

void StartupState::setInitialSnakeSpeed(const Vector2D& speed) {
	auto& snakeMovementhandler = gameContext.getSnakeMovementHandler();
	snakeMovementhandler.setSnakeSpeedIfValid(speed);
}
