#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdio>

#define ROWS 6
#define COLS 7
#define TOTAL_DIAGS 6
#define LARGEST_DIAG 7
// #define INFINITY numeric_limits<int>::infinity()
#define INFINITY 999

using namespace std;

string playerCodeToChar(int playerCode) {
	if (playerCode == 0) return "  ";
	switch (playerCode > 0) {
	case false:
		return "\u26AA"; // ⚪
	case true:
		return "\U0001f534"; // 🔴
	}
}

class Position {
private:
	vector<Position> getNextMoves() {
		vector<Position> nextMoves;
		for (int col = 0; col < COLS; col++) {
			// make sure its empty
			if (board[0][col] != 0) continue;

			Position nextMove = new Position(this);
			nextMove.makeMove(col);
			nextMoves.push_back(nextMove);
		}

		return nextMoves;
	}

public:
	int board[ROWS][COLS];
	bool isP1sTurn = true;
	int eval;
	int lastColPlayed;

	Position() {
		// set board to zeros
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				board[row][col] = 0;
			}
		}
	}
	Position(Position* oldPosition) {
		isP1sTurn = oldPosition->isP1sTurn;
		// clone board
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				board[row][col] = oldPosition->board[row][col];
			}
		}
	}

	void printBoard() {
		for (int row = 0; row < ROWS; row++) {
			cout << row << " ";
			for (int col = 0; col < COLS; col++) {
				cout << "[" << playerCodeToChar(board[row][col]) << "]";
			}
			cout << "\n";
		}

		for (int col = 1; col < COLS + 1; col++) {
			cout << "   " << col;
		}
		cout << endl;
		cout << "isP1sTurn: " << isP1sTurn << "\n";
	}

	void roughPrint(int eval) {
		cout << "Eval: " << eval << endl;
		cout << "Yet to move: " << (isP1sTurn ? 1 : -1) << endl;
		roughPrint();
	}
	void roughPrint() {
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				cout << board[row][col] << ' ';
			}
			cout << "\n";
		}
		cout << endl;
	}

	void humanTurn() {
		int col = 0;

		while (col == 0) {
			cout << "Which column would you like to play? ";
			cin >> col;

			// make sure the column has room
			if (board[0][col - 1] != 0) col = 0;
		}

		makeMove(col - 1);
	}

	int evaluate(int depth, bool initial) {
		if (abs(checkWin() == INFINITY) || depth == 0 || isBoardFull()) return checkWin();

		vector<Position> nextMoves = getNextMoves();
		Position bestMove = nextMoves.front();

		if (isP1sTurn) { // find maximum move
			int maxEval = -INFINITY;

			for (Position move : nextMoves) {
				move.eval = move.evaluate(depth - 1, false);

				if (move.eval >= maxEval) {
					maxEval = move.eval;
					bestMove = move;
				}

			}

			if (initial)
				makeMove(bestMove.lastColPlayed);
			return maxEval;
		}
		else {
			// find minimum move
			int minEval = INFINITY;

			for (Position move : nextMoves) {
				move.eval = move.evaluate(depth - 1, false);

				if (move.eval <= minEval) {
					minEval = move.eval;
					bestMove = move;
				};

			}

			if (initial)
				makeMove(bestMove.lastColPlayed);
			return minEval;
		}
	}
	void computerTurn() {
		int eval = evaluate(7, true);
		cout << "Current eval: " << eval << endl;
	}

	void makeMove(int col) {
		// loop though the col to see where to place the marker
		for (int row = 0; row < ROWS; row++) {
			// if next one is either out of bounds or is not empty
			if (board[row][col] == 0 && (row + 1 == ROWS || board[row + 1][col] != 0)) {
				board[row][col] = isP1sTurn ? 1 : -1;
			}
		}

		// update markers
		lastColPlayed = col;
		isP1sTurn = !isP1sTurn;
	}
	bool isBoardFull() {
		for (int col = 0; col < COLS; col++) {
			if (board[0][col] == 0) return false;
		}
		return true;
	}

	// void analyseSquare(int squareVal, int* connected, int* connectedPlayer, int* score)

	int checkWin() {
		int score = 0;

		// vertical wins
		for (int col = 0; col < COLS; col++) {
			int connected = 0;
			int connectedPlayer = -2; // neither a space nor a player code
			// int spacesBefore = 0;
			for (int row = 0; row < ROWS; row++) {
				// if part of a chain, increase
				if (board[row][col] == connectedPlayer) {
					connected++;

					if (board[row][col] != 0 && connected == 4) return connectedPlayer * INFINITY;
				}
				// if not part of a chain, reset the chain
				else if (connectedPlayer != -2) {
					// // if we go from a space to a chain
					if (connected > 1)
						score += connectedPlayer * connected * connected;

					connected = 1;
				}
				connectedPlayer = board[row][col];
			}

			if (connected > 1 && connectedPlayer != -2)
				score += connectedPlayer * connected * connected;

		}

		// horizontal wins
		for (int row = 0; row < ROWS; row++) {
			int connected = 1; // NO IDEA WHY THIS
			int connectedPlayer = -2; // neither a space nor a player code
			// int spacesBefore = 0;
			for (int col = 0; col < COLS; col++) {
				// if part of a chain, increase
				if (board[row][col] == connectedPlayer) {
					connected++;

					if (board[row][col] != 0 && connected == 4) return connectedPlayer * INFINITY;
				}
				// if not part of a chain, reset the chain
				else if (connectedPlayer != -2) {
					// // if we go from a space to a chain
					if (connected > 1)
						score += connectedPlayer * connected * connected;

					connected = 1;
				}
				connectedPlayer = board[row][col];
			}

			if (connected > 1 && connectedPlayer != -2)
				score += connectedPlayer * connected * connected;

		}


		// forward diagonals
		for (int diag = 4; diag < TOTAL_DIAGS + 4; diag++) {
			int connected = 0;
			int connectedPlayer = -2;
			for (int i = 0; i < LARGEST_DIAG; i++) {
				if (diag - i - 1 >= ROWS || diag - i - 1 < 0) continue;
				int boxVal = board[diag - i - 1][i];

				// if part of a chain, increase
				if (boxVal == connectedPlayer) {
					connected++;

					if (boxVal != 0 && connected == 4) return connectedPlayer * INFINITY;
				}
				// if not part of a chain, reset the chain
				else {
					if (connected > 1)
						score += connectedPlayer * connected * connected;

					connectedPlayer = boxVal;
					connected = 1;
				}
				connectedPlayer = boxVal;
			}

			if (connected > 1 && connectedPlayer != -2)
				score += connectedPlayer * connected * connected;
		}

		// backward diagonals
		for (int diag = 4; diag < TOTAL_DIAGS + 4; diag++) {
			int connected = 0;
			int connectedPlayer = -2;
			for (int i = 0; i < LARGEST_DIAG; i++) {
				if (diag - i - 1 >= ROWS || diag - i - 1 < 0) continue;
				int boxVal = board[diag - i - 1][ROWS - i];

				// if part of a chain, increase
				if (boxVal == connectedPlayer) {
					connected++;

					if (boxVal != 0 && connected == 4) return connectedPlayer * INFINITY;
				}
				// if not part of a chain, reset the chain
				else {
					if (connected > 1)
						score += connectedPlayer * connected * connected;

					connectedPlayer = boxVal;
					connected = 1;
				}
				connectedPlayer = boxVal;
			}

			if (connected > 1 && connectedPlayer != -2)
				score += connectedPlayer * connected * connected;
		}

		return score;
	}
};

int main() {
	Position game;
	while (true) {

		// game.printBoard();
		if (game.isP1sTurn) {
			// game.printBoard();
			game.humanTurn();
		}
		else
			game.computerTurn();
		// game.humanTurn();
		game.printBoard();

		int eval = game.checkWin();
		if (abs(eval) == INFINITY) break;
	}
	cout << "Winner: " << playerCodeToChar(game.checkWin()) << endl;

	return 0;
}

