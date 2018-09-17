#include "pch.h"
#include <iostream>
#include <vector>
#include "Board.h"
#include "Node.h"

using namespace std;

// Direction Reference
//   ^      0 
// <   >  3   1
//   V      2

int main()
{
	cout << "Initializing Sliding Puzzle program...\n";

	Board initial; // create initial board
	Board goal = initial; // save initial state as the solution
	Node initNode(initial, goal); // create the initial node
	initNode.shuffleBoard(30);  // amount of times to shuffle, changed manually for now
	initial = initNode.board.getBoard(); // stores the shuffled board as the initial state
	cout << "Board State after Initial Shuffle:\n";
	initial.displayBoard();
	cout << "\nSolving...\n\n";
	//vector<int> path = initNode.hillClimb(); // starts the hill climb algorithm, returns a vector<int> of the directions taken to reach the solution
	vector<int> path = initNode.solveA();
	cout << "\nPath Taken:\n";
	for (int i = 0; i < path.size(); i++) {
		cout << path[i];
	}
	cout << "\nVisual Steps:\n";
	for (int i = 0; i < path.size(); i++) {
		initial.displayBoard();
		if (path[i] != -1) initial.makeMove(path[i]);
	}
	initial.displayBoard();
	cout << "\nProgram complete, quitting...\n\n";
}

