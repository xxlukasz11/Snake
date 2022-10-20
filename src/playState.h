#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void moveSnake();
	void changeSnakeDirection(int keyCode);
};

#endif /* SRC_PLAYSTATE_H_ */
