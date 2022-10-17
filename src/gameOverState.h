#ifndef SRC_GAMEOVERSTATE_H_
#define SRC_GAMEOVERSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "appContext.h"
#include "gameContext.h"

class GameOverState : public StateBase {
public:
	GameOverState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void handleGameEnd();
	void drawEndingScreen(int snakeSize, int highestScore) const;
	void handleYesResponse();
	void handleNoResponse();

	AppContext& appContext;
	GameContext& gameContext;
};

#endif /* SRC_GAMEOVERSTATE_H_ */
