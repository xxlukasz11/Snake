#include "pauseState.h"

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		gameContext(gameContext) {
}

void PauseState::onEnter() {
	auto& snakeMovementTimer = appContext.getSnakeMovementTimer();
	snakeMovementTimer.stop();
	drawFrame();
}

void PauseState::handleStateEvent(const ALLEGRO_EVENT& event) {
	switch (event.type) {
	case ALLEGRO_EVENT_KEY_UP:
		handleControlKey(event.keyboard.keycode);
		break;
	}
}

void PauseState::handleControlKey(int keyCode) {
	if (keyCode == ALLEGRO_KEY_ESCAPE) {
		nextState(StateType::PLAY);
	}
}

void PauseState::drawFrame() {
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawFood(gameContext.getFoodContext());
	painter.drawSnake(gameContext.getSnakeContext());
	displayPauseInformation();
	painter.flushDisplay();
}

void PauseState::displayPauseInformation() {
	auto& writer = appContext.getTextWriter();
	writer.writeCenter("PAUSED");
}
