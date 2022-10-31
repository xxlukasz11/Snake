#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include "playState.h"

PlayState::PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext) :
		StateBase(stateMachine),
		app(app),
		gameContext(gameContext),
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()) {
}

void PlayState::onEnter() {
	if (!foodContext.isFoodPlanted()) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	}
	app.startFrameRateUpdates();
}

void PlayState::handleStateEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_TIMER:
		nextIteration();
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		changeSnakeDirection(event.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_KEY_UP:
		handleControlKey(event.keyboard.keycode);
		break;
	}
}

void PlayState::nextIteration() {
	const auto successfullyMoved = moveSnake();
	drawFrame();
	if (!successfullyMoved) {
		nextState(StateType::GAME_OVER);
	}
}

void PlayState::drawFrame() {
	const auto& worldMap = gameContext.getWorldMap();
	worldMap.drawMap();
	worldMap.drawSnake(snakeContext);
	worldMap.drawFood(foodContext);
	worldMap.flushDisplay();
}

bool PlayState::moveSnake() {
	if (snakeSpeedForNextMove.has_value()) {
		snakeContext.setSpeed(snakeSpeedForNextMove.value());
		snakeSpeedForNextMove.reset();
	}

	const auto& speed = snakeContext.getSpeed();
	const auto& body = snakeContext.getBody();
	const auto& headPosition = body.at(0);
	const Position newHeadPosition = { headPosition.x + speed.x, headPosition.y + speed.y };
	snakeContext.appendHeadSegment(newHeadPosition);

	if (foodContext.isFoodHere(newHeadPosition)) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	} else {
		snakeContext.eraseTailSegment();
	}

	const auto& worldMap = gameContext.getWorldMap();
	if (worldMap.isBorderHere(newHeadPosition)) {
		playErrorSound();
		return false;
	}
	return true;
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
