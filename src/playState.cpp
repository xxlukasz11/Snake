#include <allegro5/allegro.h>
#include "playState.h"

PlayState::PlayState(StateMachine& stateMachine, WorldPainter& worldPainter, SnakeContext& snakeContext) :
		StateBase(stateMachine),
		worldPainter(worldPainter),
		snakeContext(snakeContext) {
}

void PlayState::onEnter() {

}

void PlayState::handleStateEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_TIMER:
		moveSnake();
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		changeSnakeDirection(event.keyboard.keycode);
		break;
	}
}

void PlayState::moveSnake() {

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
