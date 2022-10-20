#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine);
	void onEnter() override;
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
};

#endif /* SRC_PLAYSTATE_H_ */
