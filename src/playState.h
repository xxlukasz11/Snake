#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "snakeContext.h"
#include "worldPainter.h"
#include "app.hpp"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, WorldPainter& worldPainter, SnakeContext& snakeContext, App& app);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void nextIteration();
	bool moveSnake();
	int dirToPixelSize(int speed) const;
	void changeSnakeDirection(int keyCode);

	WorldPainter& painter;
	SnakeContext& snakeContext;
	App& app;
	double pixelSize;
};

#endif /* SRC_PLAYSTATE_H_ */
