#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>
#include "basic_allegro.hpp"
#include "errMsg.hpp"
#include "gra.hpp"

const short width = 810;
const short height = 510;

class App {
public:
	Display display;
	Font font;
	ALLEGRO_MONITOR_INFO monitor;
	Queue queue;
	ALLEGRO_EVENT event;
	Timer timer;
	float dt{ 0.06f };
};


int main(int argc, char** argv) {
	// Inicjalizacja srodkowiska
	if (!install_modules())
		return -1;

	App app;
	if (!app.display.init(width, height, "Snake")) {
		errMsg r("Failed to init display");
		r.print("error.log");
		return -1;
	}
	al_get_monitor_info(0, &app.monitor);
	al_set_window_position(app.display.ptr, (app.monitor.x2 - app.monitor.x1 - app.display.width) / 2, (app.monitor.y2 - app.monitor.y1 - app.display.height) / 2);
	if (!app.font.add("Arial", 24, "arial.ttf")) {
		errMsg r("Font not found");
		r.print("error.log");
		return -1;
	}
	if (!app.timer.init(app.dt)) {
		errMsg r("Failed to init timer");
		r.print("error.log");
		return -1;
	}
	if (!al_install_keyboard()) {
		errMsg r("Failed to install keyboard");
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