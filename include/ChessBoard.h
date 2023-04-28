#pragma once
#include "GamePieces/GamePiece.h"
#include <vector>
#include <array>
#include <memory>
#include <string>

using std::string;
using std::array;
using std::vector;
using std::unique_ptr;
using std::move;
using std::tolower;


class ChessBoard {

public:
	ChessBoard(const string& start);
	int execute(const string& res);

private:
	void initBoard(const string& start);

	bool isEmpty(const Position& pos) const;
	bool isPieceOfOpponent(const Position& pos) const;
	bool isPieceOfCurPlayer(const Position& pos) const;
	bool isLegalMove(const Position& source, const Position& dest) const;
	bool isPathBlocked(const Position& source, const Position& dest) const;
	bool isMoveCausedCheck(bool onCurPlayer) const;
	bool isDifferentColor(const Position& source, const Position& dest) const;
	vector<Position> getPiecesPos(bool color) const;
	void setKingPos(bool color, const Position& newPos);
	int movePiece(const Position& source, const Position& dest);

	using GamePieceRow = array<unique_ptr<GamePiece>, BOARD_SIZE>;
	array<GamePieceRow, BOARD_SIZE> m_board;

	Position m_whiteKingPos;
	Position m_blackKingPos;
	bool m_turn = WHITE;

};