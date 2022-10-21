#ifndef SRC_PAUSESTATE_H_
#define SRC_PAUSESTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "appContext.h"

class PauseState : public StateBase {
public:
	PauseState(StateMachine& stateMachine, AppContext& appContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	AppContext& appContext;
};

#endif /* SRC_PAUSESTATE_H_ */
