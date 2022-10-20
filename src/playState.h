#ifndef SRC_PLAYSTATE_H_
#define SRC_PLAYSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "snakeContext.h"
#include "worldPainter.h"

class PlayState : public StateBase {
public:
	PlayState(StateMachine& stateMachine, WorldPainter& worldPainter, SnakeContext& snakeContext);
	void onEnter() override;
	void handleStateEvent(const ALLEGRO_EVENT& event) override;

private:
	void moveSnake();
	void changeSnakeDirection(int keyCode);

	WorldPainter& worldPainter;
	SnakeContext& snakeContext;
};

#endif /* SRC_PLAYSTATE_H_ */
