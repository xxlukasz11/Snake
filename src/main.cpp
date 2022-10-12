#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>
#include "basic_allegro.hpp"
#include "errMsg.hpp"
#include "gra.hpp"
#include "app.hpp"

int main(int argc, char** argv) {
	if (!init_alllegro_modules()) {
		return -1;
	}

	App app;
	if (!app.initDisplay()) {
		errMsg r("Failed to init display");
		r.print("error.log");
		return -1;
	}

	if (!app.loadMainFont()) {
		errMsg r("Failed to load main font");
		r.print("error.log");
		return -1;
	}

	if (!app.initFrameRateTimer()) {
		errMsg r("Failed to init timer");
		r.print("error.log");
		return -1;
	}

	app.queue.register_keyboard();
	app.queue.register_source(app.display.ptr);
	app.queue.register_source(app.timer.ptr);
	
	bool not_terminate = true;
	while (not_terminate) {
		//obiekty
		Snake snake(15, app.display.width, app.display.height, app.dt, 1, al_map_rgb(255, 0, 0), al_map_rgb(68, 136, 170), al_map_rgb(35, 121, 22), al_map_rgb(238, 230, 165));
		snake.set_start_variables(300, 300, 1, 0);
		// poczatek
		snake.intro(app.font["Arial"]);
		// pauza
		al_wait_for_event(app.queue.ptr, &app.event);
		int old_dir = ALLEGRO_KEY_RIGHT;
		if (app.event.type == ALLEGRO_EVENT_KEY_DOWN)
			old_dir = snake.change_dir(app.event.keyboard.keycode, old_dir);
		else if (app.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return 0;
		int new_dir = old_dir;
		int tmp_dir;
		snake.draw_all();
		// Glowna petla
		bool no_exit = true;
		al_start_timer(app.timer.ptr);
		while (no_exit) {
			al_wait_for_event(app.queue.ptr, &app.event);
			switch (app.event.type) {
			case ALLEGRO_EVENT_TIMER:
				if (!snake.calc())
					no_exit = false;
				snake.draw();
				al_flip_display();
				old_dir = new_dir;
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				return 0;
			case ALLEGRO_EVENT_KEY_UP:
				if (app.event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					no_exit = false;
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				tmp_dir = snake.change_dir(app.event.keyboard.keycode, old_dir);
				if (tmp_dir != old_dir)
					new_dir = tmp_dir;
				break;
			}
		}
		// pauza
		al_stop_timer(app.timer.ptr);
		snake.outro(app.font["Arial"]);
		al_flush_event_queue(app.queue.ptr);
		while (true) {
			al_wait_for_event(app.queue.ptr, &app.event);
			if (app.event.type == ALLEGRO_EVENT_KEY_UP) {
				if (app.event.keyboard.keycode == ALLEGRO_KEY_ESCAPE || app.event.keyboard.keycode == ALLEGRO_KEY_N) {
					not_terminate = false;
					break;
				}
				if (app.event.keyboard.keycode == ALLEGRO_KEY_T)
					break;
			}
			if (app.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				return 0;
		}
	} // petla programu
	return 0;
}
