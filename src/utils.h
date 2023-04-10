#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "allegro-cpp/vec.h"

using Vector2D = allegrocpp::IntVec;

struct Area {
	Vector2D topLeft;
	Vector2D bottomRight;
};

#endif /* SRC_UTILS_H_ */
