#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

struct Vector2D {
	int x;
	int y;
};

struct Area {
	Vector2D topLeft;
	Vector2D bottomRight;
};

inline bool operator==(const Vector2D& left, const Vector2D& right) {
	return left.x == right.x && left.y == right.y;
}

#endif /* SRC_UTILS_H_ */
