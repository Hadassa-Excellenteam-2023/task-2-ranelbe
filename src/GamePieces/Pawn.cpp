#include "GamePieces/Pawn.h"
#include "Factory.h"
#include "ChessBoard.h"

Pawn::Pawn(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Pawn::isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const
{
	int direction = (this->getColor() == WHITE) ? 1 : -1; //pawn's direction
	int rowDiff = dest.x - source.x;
	int colDiff = dest.y - source.y;
	
	// move forward one step or two steps if it's the first move
	if (!OpponentDest && colDiff == 0 && (rowDiff == direction || 
		rowDiff == 2 * direction && m_isFirstMove)) {
		m_isFirstMove = false;
		return true;
	}
	// can take it's opponent's piece one step forward diagonally
	else if (OpponentDest && abs(colDiff) == 1 && 
		rowDiff == direction) {
		return true;
	}

	return false;
}

// white pawn registration
bool Pawn::m_registerit_white =
Factory<GamePiece>::registerit
(
    'P', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Pawn>(WHITE); }
);

// black pawn registration
bool Pawn::m_registerit_black =
Factory<GamePiece>::registerit
(
    'p', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Pawn>(BLACK); }
);