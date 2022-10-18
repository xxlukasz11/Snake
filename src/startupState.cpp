#include "startupState.h"

StartupState::StartupState(StateMachine& stateMachine, WorldPainter& painter) :
		stateMachine(stateMachine),
		painter(painter) {
}

void StartupState::onEnter() {
	painter.draw();
}

void StartupState::handleEvent(const ALLEGRO_EVENT& event) {

}
