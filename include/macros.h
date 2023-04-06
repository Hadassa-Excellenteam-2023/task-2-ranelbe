#pragma once

const int BOARD_SIZE = 8;

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


const bool ON_CUR_PLAYER = true;
const bool ON_OPPONENT = false;