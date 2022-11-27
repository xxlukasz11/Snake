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
		changeSnakeDirection(event);
		return;
	}

	if (event.isKeyReleased()) {
		handleControlKey(event);
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

// TODO: cut off tail instead of ending the game
// TODO: display animation for tail that was cut off
	if (snakeContext.isHeadOverBodySegment()) {
		playErrorSound();
		return false;
	}

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

void PlayState::changeSnakeDirection(const framework::Event& event) {
	const auto currentSpeed = snakeContext.getSpeed();
	if (event.isKeyPressed(KeyboardKey::KEY_UP) && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, -1 };
		return;
	}

	if (event.isKeyPressed(KeyboardKey::KEY_DOWN) && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, 1 };
		return;
	}

	if (event.isKeyPressed(KeyboardKey::KEY_LEFT) && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ -1, 0 };
		return;
	}

	if (event.isKeyPressed(KeyboardKey::KEY_RIGHT) && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ 1, 0 };
		return;
	}
}

void PlayState::handleControlKey(const framework::Event& event) {
	if (event.isKeyReleased(KeyboardKey::KEY_ESCAPE)) {
		nextState(StateType::PAUSE);
	}
}
