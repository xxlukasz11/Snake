#include "stateBase.h"

StateBase::StateBase(StateMachine& stateMachine) :
		stateMachine(stateMachine) {
}

void StateBase::handleEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		exitGame();
		return;
	case ALLEGRO_EVENT_KEY_UP:
		if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			exitGame();
		}
		return;
	}
	handleStateEvent(event);
}

void StateBase::exitGame() {
	stateMachine.terminate();
}

void StateBase::nextState(StateType stateType) {
	stateMachine.setState(stateType);
}
