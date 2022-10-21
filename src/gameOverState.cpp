#include "gameOverState.h"

GameOverState::GameOverState(StateMachine& stateMachine, AppContext& appContext) :
		StateBase(stateMachine),
		appContext(appContext) {
}

void GameOverState::onEnter() {
	appContext.stopFrameRateUpdates();
}

void GameOverState::handleStateEvent(const ALLEGRO_EVENT& event) {

}
