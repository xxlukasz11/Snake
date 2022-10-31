#include <allegro5/allegro.h>
#include "appContext.h"
#include "gameStateController.h"

int main(int argc, char** argv) {
	if (!app_init_alllegro_modules()) {
		return -1;
	}

	AppContext app;
	if (!app.initialize()) {
		return -1;
	}

	ALLEGRO_EVENT event;
	GameStateController game(app);
	game.initialize();
	while (app.getRunningFlag()) {
		app.waitForEvent(event);
		game.handleEvent(event);
	}
	return 0;
}
