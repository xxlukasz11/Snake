#include <optional>
#include "startupState.h"
#include "direction.h"

using framework::Event;
using framework::KeyboardKey;

namespace {

std::optional<Direction> tryCalculatingDirection(const KeyboardKey& key) {
	if (KeyboardKey::KEY_UP == key) {
		return Direction::UP;
	}
	if (KeyboardKey::KEY_DOWN == key) {
		return Direction::DOWN;
	}
	if (KeyboardKey::KEY_LEFT == key) {
		return Direction::LEFT;
	}
	if (KeyboardKey::KEY_RIGHT == key) {
		return Direction::RIGHT;
	}
	return std::nullopt;
}

} // namespace

StartupState::StartupState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine, appContext),
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

	const auto direction = tryCalculatingDirection(event.getKey());
	if (!direction.has_value()) {
		return;
	}

	setInitialSnakeDirection(direction.value());
	nextState(StateType::PLAY);
}

void StartupState::setInitialSnakeDirection(const Direction& direction) {
	auto& snakeMovementhandler = gameContext.getSnakeMovementHandler();
	snakeMovementhandler.setSnakeDirectionIfValid(direction);
}
