#include "GamePieces/Bishop.h"
#include "Factory.h"

bool Bishop::m_registerit = GamePiece::registerPiece<Bishop>('B', 'b');

Bishop::Bishop(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Bishop::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    //move only diagonally
    return abs(dest.x - source.x) == abs(dest.y - source.y);
}