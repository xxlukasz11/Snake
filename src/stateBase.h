#ifndef SRC_STATEBASE_H_
#define SRC_STATEBASE_H_

#include "state.h"
#include "stateMachine.h"

class StateBase : public State {
public:
	StateBase(StateMachine& stateMachine);

protected:
	virtual void handleStateEvent(const framework::Event& event) = 0;
	void nextState(StateType stateType);

private:
	void exitGame();
	void handleEvent(const framework::Event& event) override;

	StateMachine& stateMachine;
};

#endif /* SRC_STATEBASE_H_ */
