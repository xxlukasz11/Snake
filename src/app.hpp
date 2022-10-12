#ifndef SRC_APP_HPP_
#define SRC_APP_HPP_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include "basic_allegro.hpp"

class App {
public:
	bool initDisplay(const std::string& displayName);

	Display display;
	Font font;
	ALLEGRO_MONITOR_INFO monitor;
	Queue queue;
	ALLEGRO_EVENT event;
	Timer timer;
	float dt{ 0.06f };
};

bool init_alllegro_modules();


#endif /* SRC_APP_HPP_ */
