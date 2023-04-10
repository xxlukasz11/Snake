#include "gameStateController.h"
#include "startupState.h"
#include "playState.h"
#include "pauseState.h"
#include "gameOverState.h"
#include "appContext.h"

GameStateController::GameStateController(AppContext& appContext) :
		gameContext(appContext.getDisplay()),
		startupState(std::make_shared<StartupState>(*this, appContext, gameContext)),
		playState(std::make_shared<PlayState>(*this, appContext, gameContext)),
		pauseState(std::make_shared<PauseState>(*this, appContext, gameContext)),
		gameOverState(std::make_shared<GameOverState>(*this, appContext, gameContext)),
		currentStateType(StateType::NONE) {
	setState(StateType::STARTUP);
}

void GameStateController::setState(StateType stateType) {
	if (currentStateType == stateType) {
		return;
	}
	currentStateType = stateType;

	switch (stateType) {
	case StateType::STARTUP:
		currentState = startupState;
		break;
	case StateType::PLAY:
		currentState = playState;
		break;
	case StateType::PAUSE:
		currentState = pauseState;
		break;
	case StateType::GAME_OVER:
		currentState = gameOverState;
		break;
	default:
		break;
	}
	currentState->onEnter();
}

void GameStateController::handleEvent(const allegrocpp::Event& event) {
	currentState->handleEvent(event);
}
