#include "GamePieces/King.h"
#include "Factory.h"


King::King(bool isWhite) :
    GamePiece(isWhite)
{
}

bool King::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only one spot in any direction
    return abs(dest.x - source.x) <= 1 && abs(dest.y - source.y) <= 1;
}

// white king registration
bool King::m_registerit_white =
Factory<GamePiece>::registerit
(
    'K', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<King>(WHITE); }
);

// black king registration
bool King::m_registerit_black =
Factory<GamePiece>::registerit
(
    'k', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<King>(BLACK); }
);