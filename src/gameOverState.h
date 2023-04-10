#ifndef SRC_GAMEOVERSTATE_H_
#define SRC_GAMEOVERSTATE_H_

#include "stateBase.h"
#include "stateMachine.h"
#include "appContext.h"
#include "gameContext.h"

class GameOverState : public StateBase {
public:
	GameOverState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext);
	void onEnter() override;
	void handleStateEvent(const allegrocpp::Event& event) override;
	void frameUpdate() override;

private:
	struct GameEndData {
		int highestScore;
		int achievedScore;
	};

	void initializeGameEndData();
	void drawInstructions() const;
	void handleYesResponse();
	void handleNoResponse();

	AppContext& appContext;
	GameContext& gameContext;
	GameEndData gameEndData;
};

#endif /* SRC_GAMEOVERSTATE_H_ */
