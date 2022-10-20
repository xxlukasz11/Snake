#ifndef SRC_STATEBASE_H_
#define SRC_STATEBASE_H_

#include <allegro5/allegro.h>

#include "state.h"
#include "stateMachine.h"

class StateBase : public State {
public:
	StateBase(StateMachine& stateMachine);

protected:
	void handleCommonEvent(const ALLEGRO_EVENT& event);
	void exitGame();
	void nextState(StateType stateType);

private:
	StateMachine& stateMachine;
};

#endif /* SRC_STATEBASE_H_ */
