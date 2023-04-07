#include "GamePieces/Bishop.h"
#include "Factory.h"


Bishop::Bishop(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Bishop::isLegalMove(const Position& source, const Position& dest) const
{
    //move only diagonally
    return abs(dest.x - source.x) == abs(dest.y - source.y);
}

// white bishop registration
bool Bishop::m_registerit_white =
Factory<GamePiece>::registerit
(
    'B', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Bishop>(WHITE); }
);

// black bishop registration
bool Bishop::m_registerit_black =
Factory<GamePiece>::registerit
(
    'b', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Bishop>(BLACK); }
);