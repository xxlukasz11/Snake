#ifndef SRC_STATEBASE_H_
#define SRC_STATEBASE_H_

#include <allegro5/allegro.h>

#include "state.h"
#include "stateMachine.h"

class StateBase : public State {
public:
	StateBase(StateMachine& stateMachine);

protected:
	virtual void handleStateEvent(const ALLEGRO_EVENT& event) = 0;
	void exitGame();
	void nextState(StateType stateType);

private:
	void handleEvent(const ALLEGRO_EVENT& event) override;

	StateMachine& stateMachine;
};

#endif /* SRC_STATEBASE_H_ */
