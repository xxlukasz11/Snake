#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>

#include "appContext.h"
#include "basic_allegro.hpp"
#include "errMsg.hpp"
#include "gra.hpp"
#include "snakeGame.h"

bool isEscapeHit(const ALLEGRO_EVENT& event) {
	return event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
}

bool isDisplayClosed(const ALLEGRO_EVENT& event) {
	return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

int main(int argc, char** argv) {
	if (!app_init_alllegro_modules()) {
		return -1;
	}

	AppContext app;
	if (!app.initialize()) {
		return -1;
	}

	const auto& display = app.getDisplay();
	ALLEGRO_EVENT event;
	SnakeGame game(app);
	game.initialize();
	while (app.getRunningFlag()) {
		app.waitForEvent(event);
		game.handleEvent(event);
	}

	bool not_terminate = false;
	while (not_terminate) {

		Snake snake(15, display.width, display.height, app.getFrameRateIntervalSeconds(), 1, al_map_rgb(255, 0, 0),
				al_map_rgb(68, 136, 170), al_map_rgb(35, 121, 22), al_map_rgb(238, 230, 165));
		snake.set_start_variables(300, 300, 1, 0);
		snake.intro(app.getMainFont());
		app.waitForEvent(event);

		int old_dir = ALLEGRO_KEY_RIGHT;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			old_dir = snake.change_dir(event.keyboard.keycode, old_dir);
		} else if (isDisplayClosed(event)) {
			return 0;
		}

		int new_dir = old_dir;
		int tmp_dir;
		snake.draw_all();

		bool no_exit = true;
		app.startFrameRateUpdates();
		while (no_exit) {
			app.waitForEvent(event);
			switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				if (!snake.calc()) {
					no_exit = false;
				}
				snake.draw();
				al_flip_display();
				old_dir = new_dir;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return 0;
			case ALLEGRO_EVENT_KEY_UP:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					no_exit = false;
				}
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				tmp_dir = snake.change_dir(event.keyboard.keycode, old_dir);
				if (tmp_dir != old_dir) {
					new_dir = tmp_dir;
				}
				break;
			}
		}

		app.stopFrameRateUpdates();
		snake.outro(app.getMainFont());
		app.flushEventQueue();
		while (true) {
			app.waitForEvent(event);
			if (isEscapeHit(event)) {
				not_terminate = false;
				break;
			}
			if (event.type == ALLEGRO_EVENT_KEY_UP) {
				if (event.keyboard.keycode == ALLEGRO_KEY_N) {
					not_terminate = false;
					break;
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_T) {
					break;
				}
			}
			if (isDisplayClosed(event)) {
				return 0;
			}
		}
	}
	return 0;
}
