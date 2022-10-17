#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "foodContext.h"
#include "worldMap.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, AppContext& app, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void nextIteration();
	bool moveSnake();
	void playErrorSound() const;
	void changeSnakeDirection(int keyCode);
	void handleControlKey(int keyCode);
	void drawFrame();

	AppContext& app;
	GameContext& gameContext;
	SnakeContext& snakeContext;
	FoodContext& foodContext;
};

#endif /* SRC_PLAYSTATE_H_ */
