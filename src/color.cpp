#include "color.h"

Color::Color() :
		Color(0, 0, 0) {
}

Color::Color(int r, int g, int b) :
		rValue(r),
		gValue(g),
		bValue(b) {
}

int Color::r() const {
	return rValue;
}

int Color::g() const {
	return gValue;
}

int Color::b() const {
	return bValue;
}

Color Color::rgb(int r, int g, int b) {
	return Color{ r, g, b };
}

