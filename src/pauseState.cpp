#include "pauseState.h"

using framework::Event;
using framework::KeyboardKey;

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine, appContext),
		appContext(appContext),
		gameContext(gameContext) {
}

void PauseState::onEnter() {
	auto& frameRateTimer = appContext.getFrameRateTimer();
	frameRateTimer.stop();
	drawFrame();
}

void PauseState::handleStateEvent(const Event& event) {
	if (event.isKeyReleased(KeyboardKey::KEY_ESCAPE)) {
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
