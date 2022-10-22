#include "startupState.h"
#include "playState.h"
#include "pauseState.h"
#include "gameOverState.h"
#include "snakeGame.h"

constexpr int RASTER_SIZE = 15;

SnakeGame::SnakeGame(AppContext& appContext) :
		appContext(appContext),
		gameContext(appContext.getDisplay(), RASTER_SIZE),
		startupState(std::make_shared<StartupState>(*this, gameContext)),
		playState(std::make_shared<PlayState>(*this, appContext, gameContext)),
		pauseState(std::make_shared<PauseState>(*this, appContext)),
		gameOverState(std::make_shared<GameOverState>(*this, appContext, gameContext)),
		currentStateType(StateType::NONE) {
}

void SnakeGame::initialize() {
	setState(StateType::STARTUP);
}

void SnakeGame::terminate() {
	appContext.stopApp();
}

void SnakeGame::setState(StateType stateType) {
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

void SnakeGame::handleEvent(const ALLEGRO_EVENT& event) {
	currentState->handleEvent(event);
}
