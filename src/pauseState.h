#ifndef SRC_PAUSESTATE_H_
#define SRC_PAUSESTATE_H_

#include "stateBase.h"
#include "stateMachine.h"

class PauseState : public StateBase {
public:
	PauseState(StateMachine& stateMachine);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
};

#endif /* SRC_PAUSESTATE_H_ */
