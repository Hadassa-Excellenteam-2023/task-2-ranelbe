#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"

class King : public GamePiece {

public:
	King(bool isWhite);
	bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;

private:
	static bool m_registerit_white;
	static bool m_registerit_black;

};