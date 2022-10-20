#ifndef SRC_GAMEOVERSTATE_H_
#define SRC_GAMEOVERSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"

class GameOverState : public StateBase {
public:
	GameOverState(StateMachine& stateMachine);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
};

#endif /* SRC_GAMEOVERSTATE_H_ */
