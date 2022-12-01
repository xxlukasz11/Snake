#include "playState.h"
#include "snakeMovementHandler.h"

using framework::Event;
using framework::KeyboardKey;

PlayState::PlayState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine, appContext),
		appContext(appContext),
		gameContext(gameContext),
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		snakeMovementHandler(gameContext.getSnakeMovementHandler()),
		frameRateTimer(appContext.getFrameRateTimer()) {
}

void PlayState::onEnter() {
	if (!foodContext.isFoodPlanted()) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	}
	frameRateTimer.start();
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
	if (event.isEventSource(frameRateTimer)) {
		nextMoveIteration();
	}
}

void PlayState::nextMoveIteration() {
	setSelectedSnakeDirection();
	snakeMovementHandler.moveSnake();
	drawFrame();
	if (isGameLost()) {
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
	const auto& sample = appContext.getErrorAudioSample();
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

bool PlayState::isGameLost() {
	const auto& worldMap = gameContext.getWorldMapContext();
	return worldMap.isBorderHere(snakeContext.getHead());
}

void PlayState::handleControlKey(const framework::KeyboardKey& key) {
	if (key == KeyboardKey::KEY_ESCAPE) {
		nextState(StateType::PAUSE);
	}
}
