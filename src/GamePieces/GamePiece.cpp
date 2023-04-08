#include "GamePieces/GamePiece.h"

GamePiece::GamePiece(bool isWhite) :
	m_color(isWhite),
	m_position(Position(-1,-1)) //dummy
{
}

bool GamePiece::getColor() const
{
	return m_color;
}

