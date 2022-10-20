#include "playState.h"

PlayState::PlayState(StateMachine& stateMachine) :
		StateBase(stateMachine) {
}

void PlayState::onEnter() {

}

void PlayState::handleEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_TIMER:
		moveSnake();
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		changeSnakeDirection(event.keyboard.keycode);
		break;
	}
	handleCommonEvent(event);
}

void PlayState::moveSnake() {

}

void PlayState::changeSnakeDirection(int keyCode) {

}
