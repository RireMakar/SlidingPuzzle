#include "pch.h"
#include "Board.h"


Board::Board() // blank board constructor, sets up solved board state
{
	int initCount = 1;
	for (int i = 0; i < 4; i++) {
		vector<int> row;
		for (int j = 0; j < 4; j++) {
			if (initCount != 16) row.push_back(initCount);
			else row.push_back(-1);
			initCount++;
		}
		board.push_back(row);
	}
}

Board::Board(vector<vector<int>> newBoard) { // sets up a board with a predefined state
	for (int i = 0; i < 4; i++) {
		vector<int> row;
		for (int j = 0; j < 4; j++) {
			row.push_back(newBoard[i][j]);
		}
		board.push_back(row);
	}
}

Board::~Board() 
{
}

void Board::setBoard(vector<vector<int>> newBoard) // sets the board as a state
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = newBoard[i][j];
		}
	}
}

vector<vector<int>> Board::getBoard() // returns the board
{
	return board;
}

int Board::getManhattan(vector<vector<int>> goal) // gets the manhattan number between the current board state and the specified goal
{
	int manhattan = 0; // sets initial manhattan as 0
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) { // loops through the board...
			if (board[i][j] > 0) { // ...and for every spot not the blank space, loops through the goal state
				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						if (goal[k][l] == board[i][j]) { // returns true when it finds where the current spot in the current state is in the goal state
							manhattan = manhattan + (abs(i - k) + abs(j - l)); // increases the manhattan based on how far away the number is.
						}
					}
				}
			}
		}
	}
	return manhattan; // returns the final manhattan. this is just a metric to show how close the board is to the goal. higher manhattan is further away.
}

void Board::makeMove(int dir) // makes a move. changes the board property of the class accordingly.
{
	tuple<int, int> space = getSpace();
	tuple<int, int> posToSwap;
	switch (dir) { // switch statement to find the space that needs to be swapped
	case 0:
		posToSwap = make_tuple(get<0>(space) - 1, get<1>(space));
		break;
	case 1:
		posToSwap = make_tuple(get<0>(space), get<1>(space) + 1);
		break;
	case 2:
		posToSwap = make_tuple(get<0>(space) + 1, get<1>(space));
		break;
	case 3:
		posToSwap = make_tuple(get<0>(space), get<1>(space) - 1);
		break;
	default:
		cout << "Invalid direction in makeMove\n";
		break;
	}
	
	board[get<0>(space)][get<1>(space)] = board[get<0>(posToSwap)][get<1>(posToSwap)]; // sets the space as the number it is being swapped with
	board[get<0>(posToSwap)][get<1>(posToSwap)] = -1; // sets the original number loc as the space
}

tuple<int, int> Board::getSpace() // finds where the space is and returns it as a tuple
{
	tuple<int, int> space;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == -1) space = make_tuple(i, j);
		}
	}
	return space;
}

void Board::displayBoard() // displays the board. uses a blank space for the space.
{
	cout << "______________________________\n\n";
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == -1) cout << "     ";
			else {
				cout << "[";
				if (board[i][j] < 10) cout << " ";
				cout << board[i][j] << "] ";
			}
		}
		cout << "\n";
	}

}

vector<int> Board::getValidMoves() // returns a vector<int> of the valid directions that a move can be made in
{
	vector<int> validMoves;
	
	tuple<int, int> loc = getSpace();

	if (get<0>(loc) != 0) validMoves.push_back(0);
	if (get<0>(loc) != 3) validMoves.push_back(2);
	if (get<1>(loc) != 0) validMoves.push_back(3);
	if (get<1>(loc) != 3) validMoves.push_back(1);
	
	return validMoves;
}
