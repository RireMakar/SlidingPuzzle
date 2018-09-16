#include "pch.h"
#include "Node.h"



Node::Node(Board brd, Board gBrd)
{
	board = brd;
	goalBoard = gBrd;
	manhattan = 0;
}


Node::~Node()
{
}

vector<int> Node::hillClimb() // hill climbing algorithm
{
	Board temp = board; // creates a new board 'temp' and sets it equal to the current state
	Board best = board; // creates a new board 'best' and sets it equal to the current state
	int dirTaken = -1; // this will be the direction that is chosen. should only remain -1 if the initial state is the solved state.
	vector<int> validMoves = board.getValidMoves(); // gets all valid moves
	for (int i = 0; i < validMoves.size(); i++) {													// loops through all valid moves...
		temp.makeMove(validMoves[i]);																// ...and makes them on temp...
		if (temp.getManhattan(goalBoard.getBoard()) < best.getManhattan(goalBoard.getBoard())) {	// ...and compares the manhattan of temp with the current best...
			best = temp;																			// ...and updates the best board and best direction if the manhattan is less.
			dirTaken = validMoves[i];
		}
		temp = board; // resets temp to the board before any move was made
	}

	if (best.getManhattan(goalBoard.getBoard()) == 0) { // if the chosen next state equals the goal state
		cout << "Solved.\n";
		path.push_back(dirTaken);	// adds the direction taken to the path
		return path;				// ...and returns it
	}
	if (best.getManhattan(goalBoard.getBoard()) >= board.getManhattan(goalBoard.getBoard())) { // if the current state has no moves that have a lower manhattan, returns path to that point.
		cout << "Local maxima reached. Not solved.\n";
		return path;
	}
	path.push_back(dirTaken);						// adds the chosen direction to the path
	Node bestChild(best, goalBoard);				// creates a new node with the chosen next state
	vector<int> newPath = bestChild.hillClimb();	// runs hillclimb on it. what this returns will be the solution/local maxima.
	for (int i = 0; i < newPath.size(); i++) {		// merges the path of the solution with this node's path
		path.push_back(newPath[i]);
	}
	return path;									// ...and finally, returns the path.
}

void Node::shuffleBoard(int amount) // gets all available moves and selects one at random, repeating as many times as specified
{
	int seed = time(NULL);
	for (int i = 0; i < amount; i++) {
		vector<int> validMoves = board.getValidMoves();
		srand(seed);
		int dir = rand() % validMoves.size();
		board.makeMove(validMoves[dir]);
		seed++;
	}
}
