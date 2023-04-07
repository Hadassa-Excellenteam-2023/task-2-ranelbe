#pragma once
#include "macros.h"

class GamePiece {

public:
	GamePiece(bool isWhite);
	virtual ~GamePiece() = default;
	virtual bool isLegalMove(const Position& source, const Position& dest) const = 0;
	bool getColor() const;

private:
	Position m_position;
	bool m_color;
	bool m_isAlive;

};