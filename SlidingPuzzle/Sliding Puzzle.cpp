#include "pch.h"
#include <iostream>
#include <vector>
#include "Board.h"
#include "Node.h"
#include <string>

using namespace std;

// Direction Reference
//   ^      0 
// <   >  3   1
//   V      2
//
// MAIN SOURCES AND REFERENCES USED:
// http://journeyofalazyprogrammer.blogspot.com/2013/10/8-puzzle-problem-solution-using.html?view=sidebar
// https://towardsdatascience.com/solve-slide-puzzle-with-hill-climbing-search-algorithm-d7fb93321325
// https://picoledelimao.github.io/blog/2015/12/06/solving-the-sliding-puzzle/

int main()
{
	cout << "Initializing Sliding Puzzle program...\n\n";

	Board initial; // create initial board
	Board goal = initial; // save initial state as the solution
	Node initNode(initial, goal); // create the initial node

	cout << "Enter amount of times to shuffle. Warning: High amounts may take longer to solve.";

	string s;
	bool has_only_digits = false;
	while (!has_only_digits) {
		cin >> s;
		has_only_digits = (s.find_first_not_of("0123456789") == string::npos);
		if (!has_only_digits) cout << "\nInvalid input. Digits only, please! Try again.\n\n";
	}

	initNode.shuffleBoard(stoi(s));  // amount of times to shuffle, changed manually for now
	initial = initNode.board.getBoard(); // stores the shuffled board as the initial state
	cout << "Board State after Initial Shuffle:\n";
	initial.displayBoard();
	
	cout << "Enter \"a\" for A*, \"h\" for Hill Climb.\n\n";
	string input;
	cin >> input;
	vector<int> path;
	switch (input[0]) {
	case 'a': 
		cout << "\nSolving...\n\n";
		path = initNode.solveA();
		break;
	case 'h':
		path = initNode.hillClimb(); // starts the hill climb algorithm, returns a vector<int> of the directions taken to reach the solution

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
		break;
	default:
		cout << "Invalid input. Shutting down...";
		return 0;
	}
	cout << "\nProgram complete, quitting...\n\n";
	cin.get();


	

	
}

