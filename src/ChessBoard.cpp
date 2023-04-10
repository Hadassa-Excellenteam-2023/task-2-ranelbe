#include "ChessBoard.h"
#include "Factory.h"
#include "GamePieces/King.h"
#include "macros.h"

/*
* ctor - init the board with the given string
* @param start - the string that represents the board
*/
ChessBoard::ChessBoard(const string& start)
{
	initBoard(start);
}

/*
* init the board with the given string
* @param start - the string that represents the board
*/
void ChessBoard::initBoard(const string& start)
{
	for (int i = 0; i < BOARD_SIZE; ++i) {
		GamePieceRow row;
		for (int j = 0; j < BOARD_SIZE; ++j) {
			int ind = i * BOARD_SIZE + j;
			auto piece = Factory<GamePiece>::create(start[ind]);
			if (piece && typeid(*piece) == typeid(King))
				setKingPos(piece->getColor(), { i,j });
			row[j] = move(piece);
		}
		m_board[i] = move(row);
	}
}

/*
* process the given input and execute the movement
* @param res - the input
* @return the response code
*/
int ChessBoard::execute(const string& res)
{
	// extract the source and destination from the given input
	Position source = { tolower(res[0]) - 'a', tolower(res[1]) - '1' };
	Position dest = { tolower(res[2]) - 'a', tolower(res[3]) - '1' };

	if (isEmpty(source)) return SRC_EMPTY;
	else if (isPieceOfOpponent(source)) return SRC_OPPONENT;
	else if (isPieceOfCurPlayer(dest)) return DEST_CUR_PLAYER;
	else if (!isLegalMove(source, dest)) return ILLEGAL_PIECE_MOVE;
	return movePiece(source, dest);
}

/*
* check if the given position is empty
* @param pos - the position to check
* @return true if the position is empty
*/
bool ChessBoard::isEmpty(const Position& pos) const
{
	return m_board[pos.x][pos.y] == nullptr;
}

/*
* check if the given position is occupied by a piece of the opponent
* @param pos - the position to check
* @return true if the position is occupied by a piece of the opponent
*/
bool ChessBoard::isPieceOfOpponent(const Position& pos) const
{
	return !isEmpty(pos) && m_board[pos.x][pos.y]->getColor() != m_turn;
}

/*
* check if the given position is occupied by a piece of the current player
* @param pos - the position to check
* @return true if the position is occupied by a piece of the current player
*/
bool ChessBoard::isPieceOfCurPlayer(const Position& pos) const
{
	return !isEmpty(pos) && m_board[pos.x][pos.y]->getColor() == m_turn;
}

/*
* check if the movement of the piece is legal
* @param source - the source position
* @param dest - the destination position
* @return true if the movement is legal
*/
bool ChessBoard::isLegalMove(const Position& source, const Position& dest) const
{
	return m_board[source.x][source.y]->isLegalMove(
		source, dest, isDifferentColor(source, dest)) &&
		!isPathBlocked(source, dest);
}

/*
* check if there is a piece between the source and the destination
* @param source - the source position
* @param dest - the destination position
* @return true if there is a piece between the source and the destination
*/
bool ChessBoard::isPathBlocked(const Position& source, const Position& dest) const
{
	int dx = dest.x - source.x;
	int dy = dest.y - source.y;

	//movement is not straight or diagonal
	if (dx != 0 && dy != 0 && dx != dy)
		return false;

	// unit vector direction
	Direction dir = { dx == 0 ? 0 : dx / abs(dx), dy == 0 ? 0 : dy / abs(dy) };

	// check if there is a piece between the source and the destination
	Position curPos = source + dir;
	while (curPos.x != dest.x || curPos.y != dest.y) {
		if (!isEmpty(curPos))
			return true;
		curPos += dir;
	}
	return false;
}

/*
* check if the move caused check
* @param onCurPlayer - check if the move caused check
*        on the current player or on the opponent
* @return true if the move caused check
*/
bool ChessBoard::isMoveCausedCheck(bool onCurPlayer) const
{
	Position kingPos = onCurPlayer ?
		(m_turn ? m_whiteKingPos : m_blackKingPos) :
		(m_turn ? m_blackKingPos : m_whiteKingPos);

	vector<Position> piecesPos = onCurPlayer ?
		(m_turn ? getPiecesPos(BLACK) : getPiecesPos(WHITE)) :
		(m_turn ? getPiecesPos(WHITE) : getPiecesPos(BLACK));

	// check if the king is in check
	for (auto& pos : piecesPos) {
		if (isLegalMove(pos, kingPos))
			return true;
	}
	return false;
}

/*
* check if source and destination are different colors
* @param source - the source position
* @param dest - the destination position
* @return true if source and destination are different colors
*/
bool ChessBoard::isDifferentColor(const Position& source, const Position& dest) const
{
	return !isEmpty(source) && !isEmpty(dest) && 
		m_board[source.x][source.y]->getColor() != m_board[dest.x][dest.y]->getColor();
}

/*
* get vector of all the pieces with the given color
* @param color - the color of the pieces
* @return vector of all the pieces with the given color
*/
vector<Position> ChessBoard::getPiecesPos(bool color) const
{
	vector<Position> piecesPos;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (m_board[i][j] && m_board[i][j]->getColor() == color)
				piecesPos.push_back({ i, j });
		}
	}
	return piecesPos;
}

/*
* set the position of the king
* @param color - the color of the king
* @param newPos - the new position of the king
*/
void ChessBoard::setKingPos(bool color, const Position& newPos)
{
	color == WHITE ? m_whiteKingPos = newPos : m_blackKingPos = newPos;
}

/*
* move the piece from the source to the destination if no check is caused
* @param source - the source position
* @param dest - the destination position
* @return the response code of that move
*/
int ChessBoard::movePiece(const Position& source, const Position& dest)
{
	unique_ptr<GamePiece> destPtr = move(m_board[dest.x][dest.y]);
	// move the piece
	m_board[dest.x][dest.y] = move(m_board[source.x][source.y]);
	m_board[source.x][source.y] = nullptr;
	if (typeid(*m_board[dest.x][dest.y]) == typeid(King))
		setKingPos(m_board[dest.x][dest.y]->getColor(), dest);

	if (isMoveCausedCheck(ON_CUR_PLAYER)) {
		// undo the move
		m_board[source.x][source.y] = move(m_board[dest.x][dest.y]);
		m_board[dest.x][dest.y] = move(destPtr);
		if (typeid(*m_board[source.x][source.y]) == typeid(King))
			setKingPos(m_board[source.x][source.y]->getColor(), source);
		return CHECK_ON_CUR_PLAYER;
	}
	// move was legal
	if (isMoveCausedCheck(ON_OPPONENT)) {
		m_turn = !m_turn; // change the turn
		return CHECK_ON_OPPONENT;
	}
	m_turn = !m_turn;
	return LEAGAL_MOVE;
}