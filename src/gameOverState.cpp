#include "gameOverState.h"

GameOverState::GameOverState(StateMachine& stateMachine) :
		StateBase(stateMachine) {
}

void GameOverState::onEnter() {

}

void GameOverState::handleEvent(const ALLEGRO_EVENT& event) {
	handleCommonEvent(event);
}
