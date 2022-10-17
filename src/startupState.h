#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "state.h"
#include "stateMachine.h"

class StartupState : public State {
public:
	StartupState(StateMachine& stateMachine);
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
};


#endif /* SRC_STARTUPSTATE_H_ */
