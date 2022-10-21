#include <allegro5/allegro.h>
#include "playState.h"

PlayState::PlayState(StateMachine& stateMachine, GameContext& gameContext, AppContext& app) :
		StateBase(stateMachine),
		gameContext(gameContext),
		app(app),
		snakeContext(gameContext.getSnakeContext()) {
}

void PlayState::onEnter() {
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
	const auto& wolrdMap = gameContext.getWolrdMap();
	wolrdMap.drawMap();
	wolrdMap.drawSnake(snakeContext);
	wolrdMap.flushDisplay();
}

bool PlayState::moveSnake() {
	const auto& speed = snakeContext.getSpeed();
	const auto& body = snakeContext.getBody();
	const auto& headPosition = body.at(0);
	const Position newHeadPosition = { headPosition.x + speed.x, headPosition.y + speed.y };
	snakeContext.appendHeadSegment(newHeadPosition);
	snakeContext.eraseTailSegment();
	return true;
}

void PlayState::changeSnakeDirection(int keyCode) {
	const auto currentSpeed = snakeContext.getSpeed();
	if (keyCode == ALLEGRO_KEY_UP && currentSpeed.y == 0) {
		snakeContext.setSpeed(SpeedVector{ 0, -1 });
		return;
	}

	if (keyCode == ALLEGRO_KEY_DOWN && currentSpeed.y == 0) {
		snakeContext.setSpeed(SpeedVector{ 0, 1 });
		return;
	}

	if (keyCode == ALLEGRO_KEY_LEFT && currentSpeed.x == 0) {
		snakeContext.setSpeed(SpeedVector{ -1, 0 });
		return;
	}

	if (keyCode == ALLEGRO_KEY_RIGHT && currentSpeed.x == 0) {
		snakeContext.setSpeed(SpeedVector{ 1, 0 });
		return;
	}
}
