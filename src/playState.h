#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldPainter.h"
#include "snakeMovementHandler.h"

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
	void playErrorSound() const;
	void changeSnakeDirection(const framework::KeyboardKey& key);
	void handleControlKey(const framework::KeyboardKey& key);
	void drawFrame();
	void setSelectedSnakeDirection();

	AppContext& app;
	GameContext& gameContext;
	SnakeContext& snakeContext;
	FoodContext& foodContext;
	framework::Timer& snakeMovementTimer;
	SnakeMovementHandler snakeMovementHandler;
	std::optional<SpeedVector> snakeSpeedForNextMove;
};

#endif /* SRC_PLAYSTATE_H_ */
