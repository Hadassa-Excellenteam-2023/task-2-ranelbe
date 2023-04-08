#include "GamePieces/Rook.h"
#include "Factory.h"


Rook::Rook(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Rook::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only in straight lines
    return source.x == dest.x || source.y == dest.y;
}

// white rook registration
bool Rook::m_registerit_white =
Factory<GamePiece>::registerit
(
    'R', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Rook>(WHITE); }
);

// black rook registration
bool Rook::m_registerit_black =
Factory<GamePiece>::registerit
(
    'r' , []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Rook>(BLACK); }
);