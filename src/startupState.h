#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "appContext.h"
#include "worldPainter.h"

class StartupState : public StateBase {
public:
	StartupState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void initializeSnakeBody();
	void writeInstructions() const;
	void handleKeyDown(int keyCode);

	AppContext& appContext;
	const WorldPainter& painter;
	SnakeContext& snakeContext;
	GameContext& gameContext;
};

#endif /* SRC_STARTUPSTATE_H_ */
