#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"

class Knight : public GamePiece {

public:
	Knight(bool isWhite);
	bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;

private:
	static bool m_registerit;
};