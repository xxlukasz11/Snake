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
#include "direction.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const framework::Event& event) override;
	void frameUpdate() override;

private:
	void nextMoveIteration();
	void playErrorSound() const;
	void changeSnakeDirection(const framework::KeyboardKey& key);
	void handleControlKey(const framework::KeyboardKey& key);
	void setSelectedSnakeDirection();
	bool isGameLost();
	void drawWorldMap();

	AppContext& appContext;
	GameContext& gameContext;
	SnakeContext& snakeContext;
	FoodContext& foodContext;
	SnakeMovementHandler& snakeMovementHandler;
	std::optional<Direction> snakeDirectionForNextMove;
};

#endif /* SRC_PLAYSTATE_H_ */
