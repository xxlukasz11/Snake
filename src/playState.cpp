#include "playState.h"

PlayState::PlayState(StateMachine& stateMachine) :
		StateBase(stateMachine) {
}

void PlayState::onEnter() {

}

void PlayState::handleEvent(const ALLEGRO_EVENT& event) {
	handleCommonEvent(event);
}
