#include "stateBase.h"

using framework::Event;
using framework::DisplayEvent;

StateBase::StateBase(StateMachine& stateMachine, AppContext& appContext) :
		stateMachine(stateMachine),
		appContext(appContext) {
}

void StateBase::handleEvent(const Event& event) {
	if (event.isDisplayEvent(DisplayEvent::CLOSE)) {
		exitGame();
		return;
	}
	handleStateEvent(event);
}

void StateBase::exitGame() {
	appContext.stopApp();
}

void StateBase::nextState(StateType stateType) {
	stateMachine.setState(stateType);
}
