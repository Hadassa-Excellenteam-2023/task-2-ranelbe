#include "GamePieces/Knight.h"
#include "Factory.h"


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

// white knight registration
bool Knight::m_registerit_white =
Factory<GamePiece>::registerit
(
    'N', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Knight>(WHITE); }
);

// black knight registration
bool Knight::m_registerit_black =
Factory<GamePiece>::registerit
(
    'n', []()->std::unique_ptr<GamePiece>
    { return std::make_unique<Knight>(BLACK); }
);