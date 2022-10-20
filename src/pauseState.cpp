#include "pauseState.h"

PauseState::PauseState(StateMachine& stateMachine) :
		StateBase(stateMachine) {
}

void PauseState::onEnter() {

}

void PauseState::handleEvent(const ALLEGRO_EVENT& event) {
	handleCommonEvent(event);
}
