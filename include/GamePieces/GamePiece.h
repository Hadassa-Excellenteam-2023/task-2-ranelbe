#pragma once
#include "macros.h"

class GamePiece {

public:
	GamePiece(bool isWhite);
	virtual ~GamePiece() = default;
	virtual bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const = 0;
	bool getColor() const;

	template <typename Piece>
	static bool registerPiece(char white, char black) {
		Factory<GamePiece>::registerit (
			white, []()->std::unique_ptr<GamePiece>
			{ return std::make_unique<Piece>(WHITE); }
		);
		Factory<GamePiece>::registerit(
			black, []()->std::unique_ptr<GamePiece>
			{ return std::make_unique<Piece>(BLACK); }
		);
		return true;
	}
private:
	Position m_position;
	bool m_color;

};