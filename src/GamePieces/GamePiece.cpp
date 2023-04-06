#include "GamePieces/GamePiece.h"

GamePiece::GamePiece(bool isWhite) :
	m_color(isWhite),
	m_position(Position(0,0)), //dummy
	m_isAlive(true)
{
}

void GamePiece::setPosition(const Position& pos)
{
	m_position = pos;
}

bool GamePiece::getColor() const
{
	return m_color;
}

