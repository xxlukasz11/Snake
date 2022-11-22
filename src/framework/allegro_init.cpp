#include "framework/allegro_init.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

constexpr const char* RESOURCES_PATH = "../resources";

namespace framework {

namespace {

AllegroInitResult failedResult(const std::string& reason) {
	return {AllegroInitStatus::FAILURE, reason};
}

AllegroInitResult successResult() {
	return {AllegroInitStatus::SUCCESS, ""};
}

void configureResourcesPath() {
	ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, RESOURCES_PATH);
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);
}

} // namespace

AllegroInitResult init_allegro() {
	if (!al_init()) {
		return failedResult("Failed to initialize allegro");
	}
	if (!al_install_audio()) {
		return failedResult("Failed to install audio");
	}
	if (!al_init_acodec_addon()) {
		return failedResult("Failed to initialize acodec addon");
	}
	if (!al_init_primitives_addon()) {
		return failedResult("Failed to initialize primitives addon");
	}
	if (!al_install_keyboard()) {
		return failedResult("Failed to install keyboard");
	}

	al_init_font_addon();
	if (!al_init_ttf_addon()) {
		return failedResult("Failed to initialize ttf addon");
	}

	configureResourcesPath();
	return successResult();
}

} // namespace framework
