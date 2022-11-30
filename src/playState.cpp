#include "playState.h"

using framework::Event;
using framework::KeyboardKey;

PlayState::PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext) :
		StateBase(stateMachine),
		app(app),
		gameContext(gameContext),
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
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
	const auto successfullyMoved = moveSnake();
	drawFrame();
	if (!successfullyMoved) {
		// TODO: display some animation -> make frame updates independent from snake movement
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

bool PlayState::moveSnake() {
	setSelectedSnakeDirection();
	const auto newHeadPosition = calculateNewHeadPosition();
	snakeContext.appendHeadSegment(newHeadPosition);

	if (foodContext.isFoodHere(newHeadPosition)) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	} else {
		snakeContext.eraseTailSegment();
	}

// TODO: display animation for tail that was cut off
	snakeContext.cutOffTailIfHeadCollided();
	const auto& worldMap = gameContext.getWorldMapContext();
	if (worldMap.isBorderHere(newHeadPosition)) {
		playErrorSound();
		return false;
	}

	return true;
}

void PlayState::setSelectedSnakeDirection() {
	if (snakeSpeedForNextMove.has_value()) {
		snakeContext.setSpeed(snakeSpeedForNextMove.value());
		snakeSpeedForNextMove.reset();
	}
}

Position PlayState::calculateNewHeadPosition() {
	const auto& speed = snakeContext.getSpeed();
	const auto& body = snakeContext.getBody();
	const auto& headPosition = body.at(0);
	return {headPosition.x + speed.x, headPosition.y + speed.y};
}

void PlayState::playErrorSound() const {
	const auto& sample = app.getErrorAudioSample();
	sample.play();
}

void PlayState::changeSnakeDirection(const framework::KeyboardKey& key) {
	const auto currentSpeed = snakeContext.getSpeed();
	if (KeyboardKey::KEY_UP == key && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, -1 };
		return;
	}

	if (KeyboardKey::KEY_DOWN == key && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, 1 };
		return;
	}

	if (KeyboardKey::KEY_LEFT == key && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ -1, 0 };
		return;
	}

	if (KeyboardKey::KEY_RIGHT == key && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ 1, 0 };
		return;
	}
}

void PlayState::handleControlKey(const framework::KeyboardKey& key) {
	if (key == KeyboardKey::KEY_ESCAPE) {
		nextState(StateType::PAUSE);
	}
}
