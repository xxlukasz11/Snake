#include "stateBase.h"
#include "appContext.h"

using framework::Event;
using framework::EventType;

StateBase::StateBase(StateMachine& stateMachine, AppContext& appContext) :
		stateMachine(stateMachine),
		appContext(appContext) {
}

void StateBase::handleEvent(const Event& event) {
	auto eventType = event.getEventType();
	if (EventType::DISPLAY_CLOSE == eventType) {
		exitGame();
		return;
	}
	handleStateEvent(event);
	if (EventType::TIMER_EXPIRED == eventType) {
		frameUpdate();
	}
}

void StateBase::exitGame() {
	appContext.stopApp();
}

void StateBase::nextState(StateType stateType) {
	stateMachine.setState(stateType);
}
