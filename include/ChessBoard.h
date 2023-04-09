#pragma once
#include "GamePieces/GamePiece.h"
#include <vector>
#include <memory>
#include <string>

using std::string;
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
	bool isLegalMove(const Position& source, const Position& dest, bool cur = false) const;
	bool isPathBlocked(const Position& source, const Position& dest) const;
	bool isMoveCausedCheck(bool onCurPlayer) const;
	int movePiece(const Position& source, const Position& dest);

	vector<Position> getPiecesPos(bool color) const;
	Position getKingPos(bool color) const;
	
	vector<vector<unique_ptr<GamePiece>>> m_board;
	
	bool mutable m_turn = WHITE;

};
