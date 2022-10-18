#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "state.h"
#include "stateMachine.h"

class PlayState : public State {
public:
	PlayState(StateMachine& stateMachine);
	void onEnter() override;
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
};

#endif /* SRC_PLAYSTATE_H_ */
