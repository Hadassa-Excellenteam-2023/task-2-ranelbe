#include "GamePieces/Knight.h"
#include "Factory.h"

bool Knight::m_registerit = GamePiece::registerPiece<Knight>('N', 'n');

Knight::Knight(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Knight::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move two spots in one direction and one spot in the other direction
	return (abs(dest.x - source.x) == 2 && abs(dest.y - source.y) == 1) ||
        (abs(dest.x - source.x) == 1 && abs(dest.y - source.y) == 2);
}