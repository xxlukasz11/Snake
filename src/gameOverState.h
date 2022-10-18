#ifndef SRC_GAMEOVERSTATE_H_
#define SRC_GAMEOVERSTATE_H_

#include "state.h"
#include "stateMachine.h"

class GameOverState : public State {
public:
	GameOverState(StateMachine& stateMachine);
	void onEnter() override;
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
};

#endif /* SRC_GAMEOVERSTATE_H_ */
