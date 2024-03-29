#ifndef SRC_STATEBASE_H_
#define SRC_STATEBASE_H_

#include "state.h"
#include "stateMachine.h"

class AppContext;

class StateBase : public State {
public:
	StateBase(StateMachine& stateMachine, AppContext& appContext);

protected:
	virtual void handleStateEvent(const allegrocpp::Event& event) = 0;
	virtual void frameUpdate() = 0;
	void nextState(StateType stateType);

private:
	void exitGame();
	void handleEvent(const allegrocpp::Event& event) override;

	StateMachine& stateMachine;
	AppContext& appContext;
};

#endif /* SRC_STATEBASE_H_ */
