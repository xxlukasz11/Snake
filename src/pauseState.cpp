#include "pauseState.h"

using allegrocpp::Event;
using allegrocpp::KeyboardKey;

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine, appContext),
		appContext(appContext),
		gameContext(gameContext) {
}

void PauseState::onEnter() {
}

void PauseState::handleStateEvent(const Event& event) {
	if (event.isKeyReleased(KeyboardKey::ESCAPE)) {
		nextState(StateType::PLAY);
	}
}

void PauseState::displayPauseInformation() {
	auto& writer = appContext.getTextWriter();
	writer.writeCenter("PAUSED");
}

void PauseState::frameUpdate() {
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawFood(gameContext.getFoodContext());
	painter.drawSnake(gameContext.getSnakeContext());
	displayPauseInformation();
	painter.flushDisplay();
}
