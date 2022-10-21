#include "startupState.h"
#include "playState.h"
#include "pauseState.h"
#include "gameOverState.h"
#include "snakeGame.h"

constexpr int PIXEL_SIZE = 15;

SnakeGame::SnakeGame(AppContext& app) :
		painter(app.getDisplay(), PIXEL_SIZE),
		startupState(std::make_shared<StartupState>(*this, painter, gameContext)),
		playState(std::make_shared<PlayState>(*this, painter, gameContext, app)),
		pauseState(std::make_shared<PauseState>(*this)),
		gameOverState(std::make_shared<GameOverState>(*this)),
		currentStateType(StateType::NONE) {
	setState(StateType::STARTUP);
}

void SnakeGame::terminate() {
	runningFlag = false;
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

bool SnakeGame::shouldBeRunning() const {
	return runningFlag;
}
