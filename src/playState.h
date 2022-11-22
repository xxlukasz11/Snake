#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldPainter.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void handleTimerEvent(const ALLEGRO_EVENT& event);
	void nextMoveIteration();
	bool moveSnake();
	void playErrorSound() const;
	void changeSnakeDirection(int keyCode);
	void handleControlKey(int keyCode);
	void drawFrame();
	void updateSnakeSpeed();
	Position calculateNewHeadPosition();

	AppContext& app;
	GameContext& gameContext;
	SnakeContext& snakeContext;
	FoodContext& foodContext;
	Timer& snakeMovementTimer;
	std::optional<SpeedVector> snakeSpeedForNextMove;
};

#endif /* SRC_PLAYSTATE_H_ */
