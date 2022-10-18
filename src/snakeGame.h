#ifndef SRC_SNAKEGAME_H_
#define SRC_SNAKEGAME_H_

#include <memory>

#include "state.h"
#include "stateMachine.h"
#include "app.hpp"
#include "worldPainter.h"
#include "snakeContext.h"

class SnakeGame : public StateMachine {
public:
	SnakeGame(App& app);
	void setState(StateType stateType) override;
	void handleEvent(const ALLEGRO_EVENT& event);

private:
	SnakeContext snakeContext;
	WorldPainter painter;
	std::shared_ptr<State> startupState;
	std::shared_ptr<State> playState;
	std::shared_ptr<State> pauseState;
	std::shared_ptr<State> gameOverState;
	std::shared_ptr<State> currentState;
	StateType currentStateType;
};

#endif /* SRC_SNAKEGAME_H_ */
