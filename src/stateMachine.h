#ifndef SRC_STATEMACHINE_H_
#define SRC_STATEMACHINE_H_

enum class StateType {
	STARTUP, INTRO, PLAY, PAUSE, GAME_OVER, NONE
};

class StateMachine {
public:
	virtual ~StateMachine() = default;
	virtual void setState(StateType stateType) = 0;
};

#endif /* SRC_STATEMACHINE_H_ */
