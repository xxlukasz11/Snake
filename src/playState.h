#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "worldMap.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, GameContext& gameContext, AppContext& app);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void nextIteration();
	bool moveSnake();
	void changeSnakeDirection(int keyCode);
	void drawFrame();

	GameContext& gameContext;
	AppContext& app;
	SnakeContext& snakeContext;
};

#endif /* SRC_PLAYSTATE_H_ */
