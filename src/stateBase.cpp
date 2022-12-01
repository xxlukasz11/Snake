#include "stateBase.h"
#include "appContext.h"

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
	if (event.isTimerEvent()) {
		frameUpdate();
	}
}

void StateBase::exitGame() {
	appContext.stopApp();
}

void StateBase::nextState(StateType stateType) {
	stateMachine.setState(stateType);
}
