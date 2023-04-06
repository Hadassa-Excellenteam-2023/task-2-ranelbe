#include "ChessBoard.h"
#include "Factory.h"
#include "GamePieces/King.h"
#include "macros.h"

ChessBoard::ChessBoard(const string& start)
{
	initBoard(start);
}

// init the board with all the pieces, '#' = nullptr
void ChessBoard::initBoard(const string& start)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		vector<unique_ptr<GamePiece>> row;
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			int ind = i * BOARD_SIZE + j;
			auto piece = Factory<GamePiece>::create(start[ind]);
			savePosition(piece, { i,j });
			row.push_back(std::move(piece));
		}
		m_board.push_back(std::move(row));
	}
}

int ChessBoard::execute(const string& res)
{
	// extract the source and destination from the given input
	Position source = { std::tolower(res[0]) - 'a', std::tolower(res[1]) - '1' };
	Position dest = { std::tolower(res[2]) - 'a', std::tolower(res[3]) - '1' };
	
	if (isEmpty(source)) 
		return 11;

	else if (isPieceOfOpponent(source))
		return 12;

	else if (isPieceOfCurPlayer(dest))
		return 13;

	else if (!isLegalMove(source, dest))
		return 21;

	return movePiece(source, dest);
}

bool ChessBoard::isEmpty(const Position& pos) const
{
	return m_board[pos.x][pos.y] == nullptr;
}

bool ChessBoard::isPieceOfOpponent(const Position& pos) const
{
	return !isEmpty(pos) && 
		m_board[pos.x][pos.y]->getColor() != m_turn;
}

bool ChessBoard::isPieceOfCurPlayer(const Position& pos) const
{
	return !isEmpty(pos) && 
		m_board[pos.x][pos.y]->getColor() == m_turn;
}

bool ChessBoard::isLegalMove(const Position& source, const Position& dest) const
{
	return m_board[source.x][source.y]->isLegalMove(source, dest) &&
		!isPathBlocked(source, dest);
}

bool ChessBoard::isPathBlocked(const Position& source, const Position& dest) const
{
	int dx = dest.x - source.x;
	int dy = dest.y - source.y;

	//movement is not straight or diagonal
	if (dx != 0 && dy != 0 && dx != dy)
		return false;
	
	// unit vector direction
	Direction dir = { dx == 0 ? 0 : dx/abs(dx), dy == 0 ? 0 : dy/abs(dy) };

	// check if there is a piece between the source and the destination
	Position curPos = source + dir;
	while (curPos.x != dest.x || curPos.y != dest.y) {
		if (!isEmpty(curPos)) 
			return true;
		curPos += dir;
	}
	return false;
}

bool ChessBoard::isMoveCausedCheck(bool onCurPlayer) const
{
	Position kingPos = onCurPlayer ?
		(m_turn ? m_whiteKingPos : m_blackKingPos) :
		(m_turn ? m_blackKingPos : m_whiteKingPos);

	vector<Position> piecesPos = onCurPlayer ?
		(m_turn ? m_blackPiecesPos : m_whitePiecesPos) :
		(m_turn ? m_whitePiecesPos : m_blackPiecesPos);

	// check if the king is in check
	for (auto& pos : piecesPos) {
		if (pos != kingPos && !isEmpty(pos) &&
			m_board[pos.x][pos.y]->isLegalMove(pos, kingPos) &&
			!isPathBlocked(pos, kingPos))
			return true;
	}
	return false;
}

void ChessBoard::savePosition(const unique_ptr<GamePiece>& piece, const Position& pos)
{
	if (piece) {
		piece->getColor() ? m_whitePiecesPos.push_back(pos) : 
							m_blackPiecesPos.push_back(pos);
		if (typeid(*piece) == typeid(King)) {
			if (piece->getColor())
				m_whiteKingPos = pos;
			else
				m_blackKingPos = pos;
		}
	}
}

int ChessBoard::movePiece(const Position& source, const Position& dest)
{
	// save the destination piece pointer
	unique_ptr<GamePiece> destPtr = std::move(m_board[dest.x][dest.y]);

	// move the piece
	m_board[dest.x][dest.y] = std::move(m_board[source.x][source.y]);
	m_board[source.x][source.y] = nullptr;
	
	if (isMoveCausedCheck(ON_CUR_PLAYER)) {
		// undo the move
		m_board[source.x][source.y] = std::move(m_board[dest.x][dest.y]);
		m_board[dest.x][dest.y] = std::move(destPtr);
		return 31;
	} 

	m_turn = !m_turn; // change the turn
	if (isMoveCausedCheck(ON_OPPONENT))
		return 41;
	return 42;
}
