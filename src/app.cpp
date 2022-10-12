#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "errMsg.hpp"
#include "app.hpp"

constexpr int DISPLAY_WIDTH = 810;
constexpr int DISPLAY_HEIGHT = 510;

bool App::initDisplay(const std::string& displayName) {
	bool initResult = display.init(DISPLAY_WIDTH, DISPLAY_HEIGHT, displayName.c_str());
	if (!initResult) {
		return initResult;
	}

	al_get_monitor_info(0, &monitor);
	al_set_window_position(display.ptr, (monitor.x2 - monitor.x1 - display.width) / 2, (monitor.y2 - monitor.y1 - display.height) / 2);
	return true;
}

bool init_alllegro_modules() {
	try {
		if (!al_init())
			throw errMsg("Failed to initialize allegro");
		if (!al_install_audio())
			throw errMsg("Failed to install audio");
		if (!al_init_acodec_addon())
			throw errMsg("Failed to initialize acodec addon");
		if (!al_init_primitives_addon())
			throw errMsg("Failed to initialize primitives addon");

		al_init_font_addon();
		if (!al_init_ttf_addon())
			throw errMsg("Failed to initialize ttf addon");
	}
	catch (errMsg r) {
		r.print("error.log");
		return false;
	}

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "../resources");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	return true;
}
