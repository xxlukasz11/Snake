#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include "allegro-cpp/event.h"

class State {
public:
	virtual ~State() = default;
	virtual void onEnter() = 0;
	virtual void handleEvent(const allegrocpp::Event& event) = 0;
};

#endif /* SRC_STATE_H_ */
