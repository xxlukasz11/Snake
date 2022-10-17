#ifndef SRC_INTROSTATE_H_
#define SRC_INTROSTATE_H_

#include "state.h"
#include "stateMachine.h"

class IntroState : public State {
public:
	IntroState(StateMachine& stateMachine);
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
};

#endif /* SRC_INTROSTATE_H_ */
