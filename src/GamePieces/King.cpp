#include "GamePieces/King.h"
#include "Factory.h"

bool King::m_registerit = GamePiece::registerPiece<King>('K', 'k');

King::King(bool isWhite) :
    GamePiece(isWhite)
{
}

bool King::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only one spot in any direction
    return abs(dest.x - source.x) <= 1 && abs(dest.y - source.y) <= 1;
}