#ifndef SRC_PAUSESTATE_H_
#define SRC_PAUSESTATE_H_

#include "state.h"
#include "stateMachine.h"

class PauseState : public State {
public:
	PauseState(StateMachine& stateMachine);
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
};

#endif /* SRC_PAUSESTATE_H_ */
