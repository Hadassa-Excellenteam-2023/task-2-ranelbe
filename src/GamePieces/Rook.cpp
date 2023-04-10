#include "GamePieces/Rook.h"
#include "Factory.h"

bool Rook::m_registerit = GamePiece::registerPiece<Rook>('R', 'r');

Rook::Rook(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Rook::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only in straight lines
    return source.x == dest.x || source.y == dest.y;
}