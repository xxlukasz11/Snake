#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "appContext.h"
#include "stateBase.h"
#include "stateMachine.h"
#include "gameContext.h"
#include "snakeContext.h"
#include "worldPainter.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, WorldPainter& worldPainter, GameContext& gameContext, AppContext& app);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void nextIteration();
	bool moveSnake();
	int dirToPixelSize(int speed) const;
	void changeSnakeDirection(int keyCode);
	void drawFrame();

	WorldPainter& painter;
	SnakeContext& snakeContext;
	AppContext& app;
	double pixelSize;
};

#endif /* SRC_PLAYSTATE_H_ */
