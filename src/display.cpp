#include "display.h"
#include <iostream>

Display::~Display() {
	if (ptr) {
		al_destroy_display(ptr);
		ptr = nullptr;
	}
}

bool Display::init(int widthRasters, int heightRasters, int rasterSize, const char* _name) {
	this->rasterSize = rasterSize;
	this->widthRasters = widthRasters;
	this->heightRasters = heightRasters;
	width = widthRasters * rasterSize;
	height = heightRasters * rasterSize;

	ptr = al_create_display(width, height);
	al_set_window_title(ptr, _name);
	if (ptr) {
		return true;
	}
	std::cerr << "Failed to create display: " << _name << std::endl;
	return false;
}

void Display::destroy() {
	if (ptr) {
		al_destroy_display(ptr);
		ptr = nullptr;
		width = 0;
		height = 0;
	}
}
