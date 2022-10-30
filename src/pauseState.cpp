#include <allegro5/allegro_font.h>
#include "pauseState.h"

PauseState::PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		gameContext(gameContext) {
}

void PauseState::onEnter() {
	appContext.stopFrameRateUpdates();
	const auto& display = appContext.getDisplay();
	al_draw_text(appContext.getMainFont(), al_map_rgb(0, 0, 0), display.width / 2, display.height / 2,
			ALLEGRO_ALIGN_CENTRE, "PAUSED");
	const auto& worldMap = gameContext.getWorldMap();
	worldMap.flushDisplay();
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
