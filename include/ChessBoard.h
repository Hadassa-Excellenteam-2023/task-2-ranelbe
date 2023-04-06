#pragma once
#include "GamePieces/GamePiece.h"
#include <vector>
#include <memory>
#include <string>


using std::string;
using std::vector;
using std::unique_ptr;

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
	void savePosition(const unique_ptr<GamePiece>& piece, const Position& pos);
	int movePiece(const Position& source, const Position& dest);

	vector<vector<unique_ptr<GamePiece>>> m_board;
	vector <Position> m_whitePiecesPos;
	vector <Position> m_blackPiecesPos;
	bool m_turn = true;
	Position m_whiteKingPos;
	Position m_blackKingPos;
};
