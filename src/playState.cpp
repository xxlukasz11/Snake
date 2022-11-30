#include "playState.h"
#include "snakeMovementHandler.h"

using framework::Event;
using framework::KeyboardKey;

PlayState::PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext) :
		StateBase(stateMachine),
		app(app),
		gameContext(gameContext),
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		snakeMovementHandler(gameContext.getSnakeMovementHandler()),
		snakeMovementTimer(app.getSnakeMovementTimer()) {
}

void PlayState::onEnter() {
	if (!foodContext.isFoodPlanted()) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	}
	snakeMovementTimer.start();
}

void PlayState::handleStateEvent(const Event& event) {
	if (event.isTimerEvent()) {
		handleTimerEvent(event);
		return;
	}

	if (event.isKeyPressed()) {
		changeSnakeDirection(event.getKey());
		return;
	}

	if (event.isKeyReleased()) {
		handleControlKey(event.getKey());
		return;
	}
}

void PlayState::handleTimerEvent(const Event& event) {
	if (event.isEventSource(snakeMovementTimer)) {
		nextMoveIteration();
	}
}

void PlayState::nextMoveIteration() {
	setSelectedSnakeDirection();
	snakeMovementHandler.moveSnake();
	drawFrame();
	if (snakeMovementHandler.gameEnded()) {
		// TODO: display some animation -> make frame updates independent from snake movement
		playErrorSound();
		nextState(StateType::GAME_OVER);
	}
}

void PlayState::drawFrame() {
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawSnake(snakeContext);
	painter.drawFood(foodContext);
	painter.flushDisplay();
}

void PlayState::setSelectedSnakeDirection() {
	if (snakeDirectionForNextMove.has_value()) {
		snakeMovementHandler.setSnakeDirectionIfValid(snakeDirectionForNextMove.value());
		snakeDirectionForNextMove.reset();
	}
}

void PlayState::playErrorSound() const {
	const auto& sample = app.getErrorAudioSample();
	sample.play();
}

void PlayState::changeSnakeDirection(const framework::KeyboardKey& key) {
	if (KeyboardKey::KEY_UP == key) {
		snakeDirectionForNextMove = Direction::UP;
		return;
	}

	if (KeyboardKey::KEY_DOWN == key) {
		snakeDirectionForNextMove = Direction::DOWN;
		return;
	}

	if (KeyboardKey::KEY_LEFT == key) {
		snakeDirectionForNextMove = Direction::LEFT;
		return;
	}

	if (KeyboardKey::KEY_RIGHT == key) {
		snakeDirectionForNextMove = Direction::RIGHT;
		return;
	}
}

void PlayState::handleControlKey(const framework::KeyboardKey& key) {
	if (key == KeyboardKey::KEY_ESCAPE) {
		nextState(StateType::PAUSE);
	}
}
