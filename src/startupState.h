#ifndef SRC_STARTUPSTATE_H_
#define SRC_STARTUPSTATE_H_

#include "state.h"
#include "stateMachine.h"
#include "worldPainter.h"

class StartupState : public State {
public:
	StartupState(StateMachine& stateMachine, WorldPainter& painter);
	void handleEvent(const ALLEGRO_EVENT& event) override;

private:
	StateMachine& stateMachine;
	WorldPainter& painter;
};


#endif /* SRC_STARTUPSTATE_H_ */
