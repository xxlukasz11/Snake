#ifndef SRC_GAMESTATECONTROLLER_H_
#define SRC_GAMESTATECONTROLLER_H_

#include <memory>

#include "state.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "worldPainter.h"
#include "framework/event.h"

class AppContext;

class GameStateController : public StateMachine {
public:
	GameStateController(AppContext& appContext);
	void setState(StateType stateType) override;
	void handleEvent(const framework::Event& event);

private:
	GameContext gameContext;
	std::shared_ptr<State> startupState;
	std::shared_ptr<State> playState;
	std::shared_ptr<State> pauseState;
	std::shared_ptr<State> gameOverState;
	std::shared_ptr<State> currentState;
	StateType currentStateType;
};

#endif /* SRC_GAMESTATECONTROLLER_H_ */
