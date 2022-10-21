#ifndef SRC_SNAKEGAME_H_
#define SRC_SNAKEGAME_H_

#include <memory>

#include "appContext.h"
#include "state.h"
#include "stateMachine.h"
#include "worldPainter.h"
#include "gameContext.h"

class SnakeGame : public StateMachine {
public:
	SnakeGame(AppContext& appContext);
	void setState(StateType stateType) override;
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

#endif /* SRC_SNAKEGAME_H_ */
