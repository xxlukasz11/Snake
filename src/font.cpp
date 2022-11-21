#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "font.h"

Font::~Font() {
	for (const auto& ob : fontArray) {
		al_destroy_font(ob.second);
	}
}

bool Font::add(const char* _name, int _size, const char* _filename) {
	ALLEGRO_FONT* f = nullptr;
	f = al_load_ttf_font(_filename, _size, 0);
	if (!f) {
		return false;
	}
	fontArray.insert(std::make_pair(_name, f));
	return true;
}

ALLEGRO_FONT* Font::operator[](const std::string& _name) const {
	auto itr = fontArray.find(_name);
	if (itr != fontArray.end()) {
		return itr->second;
	}
	std::cerr << "Font not found: " << _name << std::endl;
	return nullptr;
}
