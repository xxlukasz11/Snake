#include <iostream>
#include "appContext.h"
#include "gameStateController.h"
#include "allegro-cpp/allegroInit.h"

int main(int argc, char** argv) {
	auto [status, errorMessage] = allegrocpp::initializeAllegroModules();
	if (status != allegrocpp::AllegroInitStatus::SUCCESS) {
		std::cerr << "Cannot start application. Reason: " << errorMessage << std::endl;
		return -1;
	}

	AppContext app;
	if (!app.initialize()) {
		return -1;
	}

	GameStateController game(app);
	while (app.shouldBeRunning()) {
		auto event = app.waitForEvent();
		game.handleEvent(event);
	}
	return 0;
}
