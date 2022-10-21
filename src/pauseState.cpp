#include "pauseState.h"

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext) :
		StateBase(stateMachine),
		appContext(appContext) {
}

void PauseState::onEnter() {
	appContext.stopFrameRateUpdates();
}

void PauseState::handleStateEvent(const ALLEGRO_EVENT& event) {

}
