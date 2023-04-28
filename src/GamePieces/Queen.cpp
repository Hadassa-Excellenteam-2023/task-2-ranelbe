#include "GamePieces/Queen.h"
#include "Factory.h"

bool Queen::m_registerit = GamePiece::registerPiece<Queen>('Q', 'q');

Queen::Queen(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Queen::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move stright or diagonally
    return (source.x == dest.x || source.y == dest.y) ||
        (abs(dest.x - source.x) == abs(dest.y - source.y));   
}