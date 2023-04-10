#pragma once
#include <Factory.h>

constexpr int BOARD_SIZE = 8;

struct Direction {
	int x;
	int y;
};

struct Position {
	int x;
	int y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Position& other) const {
		return !(*this == other);
	}

	Position operator+(const Position& other) const {
		return { x + other.x, y + other.y };
	}

	Position& operator+=(const Position& other) {
		*this = *this + other;
		return *this;
	}

	Position operator+(const Direction& dir) const {
		return { x + dir.x, y + dir.y };
	}

	Position& operator+=(const Direction& dir) {
		*this = *this + dir;
		return *this;
	}
};

enum MoveError {
	SRC_EMPTY = 11,
	SRC_OPPONENT = 12,
	DEST_CUR_PLAYER = 13,
	ILLEGAL_PIECE_MOVE = 21,
	CHECK_ON_CUR_PLAYER = 31,
	CHECK_ON_OPPONENT = 41,
	LEAGAL_MOVE = 42,
};

const bool WHITE = true;
const bool BLACK = false;
const bool ON_CUR_PLAYER = true;
const bool ON_OPPONENT = false;