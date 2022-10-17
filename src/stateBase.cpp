#include "stateBase.h"

StateBase::StateBase(StateMachine& stateMachine) :
		stateMachine(stateMachine) {
}

void StateBase::handleEvent(const ALLEGRO_EVENT& event) {
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		exitGame();
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
