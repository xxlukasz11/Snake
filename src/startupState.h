#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "worldPainter.h"
#include "gameContext.h"
#include "snakeContext.h"

class StartupState : public StateBase {
public:
	StartupState(StateMachine& stateMachine, WorldPainter& painter, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void handleKeyDown(int keyCode);

	WorldPainter& painter;
	SnakeContext& snakeContext;
};

#endif /* SRC_STARTUPSTATE_H_ */
