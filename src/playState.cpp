#include "playState.h"
#include "snakeMovementHandler.h"

using allegrocpp::Event;
using allegrocpp::EventType;
using allegrocpp::KeyboardKey;

PlayState::PlayState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine, appContext),
		appContext(appContext),
		gameContext(gameContext),
		snakeContext(gameContext.getSnakeContext()),
		foodContext(gameContext.getFoodContext()),
		snakeMovementHandler(gameContext.getSnakeMovementHandler()) {
}

void PlayState::onEnter() {
	if (!foodContext.isFoodPlanted()) {
		foodContext.placeFoodOnAvailableSquares(snakeContext);
	}
}

void PlayState::handleStateEvent(const Event& event) {
	auto eventType = event.getEventType();
	if (EventType::KEY_PRESSED == eventType) {
		changeSnakeDirection(event.getKey());
		return;
	}

	if (EventType::KEY_RELEASED == eventType) {
		handleControlKey(event.getKey());
		return;
	}
}

void PlayState::nextMoveIteration() {
	setSelectedSnakeDirection();
	snakeMovementHandler.moveSnake();
	drawWorldMap();
	if (isGameLost()) {
		// TODO: display some animation -> make frame updates independent from snake movement
		playErrorSound();
		nextState(StateType::GAME_OVER);
	}
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

void PlayState::changeSnakeDirection(const allegrocpp::KeyboardKey& key) {
	if (KeyboardKey::UP == key) {
		snakeDirectionForNextMove = Direction::UP;
		return;
	}

	if (KeyboardKey::DOWN == key) {
		snakeDirectionForNextMove = Direction::DOWN;
		return;
	}

	if (KeyboardKey::LEFT == key) {
		snakeDirectionForNextMove = Direction::LEFT;
		return;
	}

	if (KeyboardKey::RIGHT == key) {
		snakeDirectionForNextMove = Direction::RIGHT;
		return;
	}
}

bool PlayState::isGameLost() {
	const auto& worldMap = gameContext.getWorldMapContext();
	return worldMap.isBorderHere(snakeContext.getHead());
}

void PlayState::handleControlKey(const allegrocpp::KeyboardKey& key) {
	if (key == KeyboardKey::ESCAPE) {
		nextState(StateType::PAUSE);
	}
}

void PlayState::frameUpdate() {
	nextMoveIteration();
}

void PlayState::drawWorldMap() {
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawSnake(snakeContext);
	painter.drawFood(foodContext);
	painter.flushDisplay();
}

