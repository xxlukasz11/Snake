#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "worldPainter.h"
#include "snakeContext.h"

class StartupState : public StateBase {
public:
	StartupState(StateMachine& stateMachine, WorldPainter& painter, SnakeContext& snakeContext);
	void onEnter() override;
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	WorldPainter& painter;
	SnakeContext& snakeContext;
};

#endif /* SRC_STARTUPSTATE_H_ */
