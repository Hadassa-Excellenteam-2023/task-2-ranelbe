#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"

class Rook : public GamePiece {

public:
	Rook(bool isWhite);
	bool isLegalMove(const Position& source, const Position& dest) const override;

private:
	static bool m_registerit_white;
	static bool m_registerit_black;

};