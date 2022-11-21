#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include <allegro5/allegro.h>

class Display {
public:
	ALLEGRO_DISPLAY* ptr{ nullptr };
	int width{ 0 };
	int height{ 0 };
	int widthRasters;
	int heightRasters;
	int rasterSize;
	~Display();
	bool init(int widthRasters, int heightRasters, int rasterSize, const char* _name = "Unnamed display");
	void destroy();
};

#endif /* SRC_DISPLAY_H_ */
