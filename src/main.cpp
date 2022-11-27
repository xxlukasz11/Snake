#include <iostream>
#include "appContext.h"
#include "gameStateController.h"
#include "framework/allegro_init.h"

int main(int argc, char** argv) {
	auto [status, errorMessage] = framework::init_allegro();
	if (status != framework::AllegroInitStatus::SUCCESS) {
		std::cerr << "Cannot start application. Reason: " << errorMessage << std::endl;
		return -1;
	}

	AppContext app;
	if (!app.initialize()) {
		return -1;
	}

	// TODO: create wrapper for Event, so that there is no dependency to Allegro
	GameStateController game(app);
	while (app.getRunningFlag()) {
		auto event = app.waitForEvent();
		game.handleEvent(event);
	}
	return 0;
}
