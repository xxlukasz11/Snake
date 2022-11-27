#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldPainter.h"

namespace framework {
class Timer;
}

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const framework::Event& event) override;

private:
	void handleTimerEvent(const framework::Event& event);
	void nextMoveIteration();
	bool moveSnake();
	void playErrorSound() const;
	void changeSnakeDirection(const framework::Event& event);
	void handleControlKey(const framework::Event& event);
	void drawFrame();
	void setSelectedSnakeDirection();
	Position calculateNewHeadPosition();

	AppContext& app;
	GameContext& gameContext;
	SnakeContext& snakeContext;
	FoodContext& foodContext;
	framework::Timer& snakeMovementTimer;
	std::optional<SpeedVector> snakeSpeedForNextMove;
};

#endif /* SRC_PLAYSTATE_H_ */
