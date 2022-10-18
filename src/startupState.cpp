#include "startupState.h"

StartupState::StartupState(StateMachine& stateMachine, WorldPainter& painter, SnakeContext& snakeContext) :
		stateMachine(stateMachine),
		painter(painter),
		snakeContext(snakeContext) {
}

void StartupState::onEnter() {
	snakeContext.appendHeadSegment( { 300, 300 });
	painter.drawMap();
	painter.drawSnake(snakeContext);
	painter.flushDisplay();
}

void StartupState::handleEvent(const ALLEGRO_EVENT& event) {

}
