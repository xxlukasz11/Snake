#ifndef SRC_GAMESTATECONTROLLER_H_
#define SRC_GAMESTATECONTROLLER_H_

#include <memory>

#include "appContext.h"
#include "state.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "worldMap.h"

class GameStateController : public StateMachine {
public:
	GameStateController(AppContext& appContext);
	void setState(StateType stateType) override;
	void initialize();
	void terminate() override;
	void handleEvent(const ALLEGRO_EVENT& event);

private:
	AppContext& appContext;
	GameContext gameContext;
	std::shared_ptr<State> startupState;
	std::shared_ptr<State> playState;
	std::shared_ptr<State> pauseState;
	std::shared_ptr<State> gameOverState;
	std::shared_ptr<State> currentState;
	StateType currentStateType;
};

#endif /* SRC_GAMESTATECONTROLLER_H_ */