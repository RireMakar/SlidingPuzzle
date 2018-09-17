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

vector<int> Node::solveA()
{
	priority_queue<Node> states;
	vector<Node> visitedStates;
	Node initial(board, goalBoard);
	states.push(initial);
	while (states.size() > 0) {
		Node state = states.top();
		state.board.displayBoard();
		visitedStates.push_back(states.top());
		states.pop();
		if (state.board.getManhattan(goalBoard.getBoard()) == 0) {
			return path;
		}
		vector<Node> children = state.visit(state.board);
		for (int i = 0; i < children.size(); i++) {
			Node child = children[i];
			bool childVisited = false;
			for (int i = 0; i < visitedStates.size(); i++) {
				if (visitedStates[i].board == child.board) {
					childVisited = true;
					break;
				}
			}
			if (!childVisited) states.push(child);
		}
	}
}

vector<Node> Node::visit(Board brd)
{
	vector<Node> children;
	vector<int> validMoves = brd.getValidMoves();
	for (int i = 0; i < validMoves.size(); i++) {
		Node newInstance(brd, goalBoard);
		newInstance.board.makeMove(validMoves[i]);
		newInstance.path.push_back(validMoves[i]);
		children.push_back(newInstance);
	}

	return children;
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

bool operator<(Node a, Node b)
{
	return a.board.getManhattan(a.goalBoard.getBoard()) + a.path.size()  > b.board.getManhattan(b.goalBoard.getBoard()) + b.path.size();
}

bool operator==(Node a, Node b)
{
	return a.board.getManhattan(a.goalBoard.getBoard()) == b.board.getManhattan(b.goalBoard.getBoard());
}
