#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

struct Position {
	int x;
	int y;
};

inline bool operator==(const Position& left, const Position& right) {
	return left.x == right.x && left.y == right.y;
}

#endif /* SRC_POSITION_H_ */
