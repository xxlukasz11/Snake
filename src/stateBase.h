#ifndef SRC_STATEBASE_H_
#define SRC_STATEBASE_H_

#include "state.h"
#include "stateMachine.h"
#include "appContext.h"

class StateBase : public State {
public:
	StateBase(StateMachine& stateMachine, AppContext& appContext);

protected:
	virtual void handleStateEvent(const framework::Event& event) = 0;
	void nextState(StateType stateType);

private:
	void exitGame();
	void handleEvent(const framework::Event& event) override;

	StateMachine& stateMachine;
	AppContext& appContext;
};

#endif /* SRC_STATEBASE_H_ */
