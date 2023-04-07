#include "GamePieces/Queen.h"
#include "Factory.h"


Queen::Queen(bool isWhite) :
    GamePiece(isWhite)
{
}

bool Queen::isLegalMove(const Position& source, const Position& dest) const
{
    // move stright or diagonally
    return (source.x == dest.x || source.y == dest.y) ||
        (abs(dest.x - source.x) == abs(dest.y - source.y));   
}

// white queen registration
bool Queen::m_registerit_white =
Factory<GamePiece>::registerit
(
    'Q', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Queen>(WHITE); }
);

// black queen registration
bool Queen::m_registerit_black =
Factory<GamePiece>::registerit
(
    'q', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Queen>(BLACK); }
);