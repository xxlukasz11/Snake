#ifndef SRC_PAUSESTATE_H_
#define SRC_PAUSESTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "appContext.h"
#include "gameContext.h"

class PauseState : public StateBase {
public:
	PauseState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const framework::Event& event) override;
	void drawFrame() override;

private:
	void displayPauseInformation();

	AppContext& appContext;
	GameContext& gameContext;
};

#endif /* SRC_PAUSESTATE_H_ */
