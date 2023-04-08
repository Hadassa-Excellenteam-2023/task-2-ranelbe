#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include <optional>

class Pawn : public GamePiece {

public:
	Pawn(bool isWhite);
	bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
private:
	static bool m_registerit_white;
	static bool m_registerit_black;
	bool mutable m_isFirstMove = true;
};