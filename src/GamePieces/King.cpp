#include "GamePieces/King.h"
#include "Factory.h"


King::King(bool isWhite) :
    GamePiece(isWhite)
{
}

bool King::isLegalMove(const Position& source, const Position& dest) const
{
    return true;
}

// white king registration
bool King::m_registerit_white =
Factory<GamePiece>::registerit
(
    'K', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<King>(true); }
);

// black king registration
bool King::m_registerit_black =
Factory<GamePiece>::registerit
(
    'k', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<King>(false); }
);