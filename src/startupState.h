#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "state.h"
#include "stateMachine.h"
#include "worldPainter.h"
#include "snakeContext.h"

class StartupState : public State {
public:
	StartupState(StateMachine& stateMachine, WorldPainter& painter, SnakeContext& snakeContext);
	void onEnter() override;
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
	WorldPainter& painter;
	SnakeContext& snakeContext;
};

#endif /* SRC_STARTUPSTATE_H_ */
