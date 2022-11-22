#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include "playState.h"

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

void PlayState::handleStateEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_TIMER:
		handleTimerEvent(event);
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		changeSnakeDirection(event.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_KEY_UP:
		handleControlKey(event.keyboard.keycode);
		break;
	}
}

void PlayState::handleTimerEvent(const ALLEGRO_EVENT& event) {
	if (snakeMovementTimer.isSourceOf(event)) {
		nextMoveIteration();
	}
}

void PlayState::nextMoveIteration() {
	const auto successfullyMoved = moveSnake();
	drawFrame();
	if (!successfullyMoved) {
		// TODO: display some animation -> make frame updates independent form snake movement
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
	updateSnakeSpeed();
	const auto newHeadPosition = calculateNewHeadPosition();
	snakeContext.appendHeadSegment(newHeadPosition);

	if (foodContext.isFoodHere(newHeadPosition)) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	} else {
		snakeContext.eraseTailSegment();
	}

	const auto& worldMap = gameContext.getWorldMapContext();
	if (worldMap.isBorderHere(newHeadPosition)) {
		playErrorSound();
		return false;
	}
	return true;
}

void PlayState::updateSnakeSpeed() {
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

void PlayState::changeSnakeDirection(int keyCode) {
	const auto currentSpeed = snakeContext.getSpeed();
	if (keyCode == ALLEGRO_KEY_UP && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, -1 };
		return;
	}

	if (keyCode == ALLEGRO_KEY_DOWN && currentSpeed.y == 0) {
		snakeSpeedForNextMove = SpeedVector{ 0, 1 };
		return;
	}

	if (keyCode == ALLEGRO_KEY_LEFT && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ -1, 0 };
		return;
	}

	if (keyCode == ALLEGRO_KEY_RIGHT && currentSpeed.x == 0) {
		snakeSpeedForNextMove = SpeedVector{ 1, 0 };
		return;
	}
}

void PlayState::handleControlKey(int keyCode) {
	if (keyCode == ALLEGRO_KEY_ESCAPE) {
		nextState(StateType::PAUSE);
	}
}
