#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "appContext.h"
#include "worldMapPainter.h"

class StartupState : public StateBase {
public:
	StartupState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void writeInstructions() const;
	void handleKeyDown(int keyCode);

	AppContext& appContext;
	const WorldMapPainter& worldMap;
	SnakeContext& snakeContext;
};

#endif /* SRC_STARTUPSTATE_H_ */
