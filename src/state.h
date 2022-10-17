#ifndef SRC_STATE_H_
#define SRC_STATE_H_

#include <allegro5/allegro.h>

class State {
public:
	virtual ~State() = default;
	virtual void onEnter() = 0;
	virtual void handleEvent(const ALLEGRO_EVENT& event) = 0;
};

#endif /* SRC_STATE_H_ */
