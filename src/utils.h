#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

struct Position {
	int x;
	int y;
};

struct Area {
	Position topLeft;
	Position bottomRight;
};

inline bool operator==(const Position& left, const Position& right) {
	return left.x == right.x && left.y == right.y;
}

#endif /* SRC_UTILS_H_ */
