#include "pauseState.h"
#include "textWriter.h"

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		gameContext(gameContext) {
}

void PauseState::onEnter() {
	appContext.stopFrameRateUpdates();
	displayPauseInformation();
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

void PauseState::displayPauseInformation() {
	TextWriter writer(appContext.getDisplay(), appContext.getMainFont());
	writer.writeCenter("PAUSED");
	const auto& worldMap = gameContext.getWorldMap();
	worldMap.flushDisplay();
}
