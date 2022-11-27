#include "stateBase.h"

using framework::Event;
using framework::DisplayEvent;

StateBase::StateBase(StateMachine& stateMachine) :
		stateMachine(stateMachine) {
}

void StateBase::handleEvent(const Event& event) {
	if (event.isDisplayEvent(DisplayEvent::CLOSE)) {
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
