#ifndef SRC_GAMEOVERSTATE_H_
#define SRC_GAMEOVERSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "appContext.h"

class GameOverState : public StateBase {
public:
	GameOverState(StateMachine& stateMachine, AppContext& appContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	AppContext& appContext;
};

#endif /* SRC_GAMEOVERSTATE_H_ */
