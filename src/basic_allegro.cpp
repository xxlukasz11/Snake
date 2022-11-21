#include "basic_allegro.h"

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

Font::~Font() {
	for (const auto& ob : font_array) {
		al_destroy_font(ob.second);
	}
}

bool Font::add(const char* _name, int _size, const char* _filename) {
	ALLEGRO_FONT* f = nullptr;
	f = al_load_ttf_font(_filename, _size, 0);
	if (!f) {
		return false;
	}
	font_array.insert(std::make_pair(_name, f));
	return true;
}

ALLEGRO_FONT* Font::operator[](const std::string& _name) const {
	auto itr = font_array.find(_name);
	if (itr != font_array.end()) {
		return itr->second;
	}
	std::cerr << "Font not found: " << _name << std::endl;
	return nullptr;
}

void wait_for_any_key() {
	auto tmp_q = al_create_event_queue();
	al_register_event_source(tmp_q, al_get_keyboard_event_source());
	ALLEGRO_EVENT ev;
	al_wait_for_event(tmp_q, &ev);
	al_destroy_event_queue(tmp_q);
}
