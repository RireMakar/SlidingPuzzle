#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include "Board.h"
#include <time.h>
#include <queue>

using namespace std;

class Node
{
public:
	// vars
	int manhattan;
	vector<int> path;
	Board board;
	Board goalBoard;
	//functions
	Node(Board brd, Board gBrd);
	~Node();
	vector<int> hillClimb();
	vector<int> solveA();
	vector<Node> visit(Board brd);
	void shuffleBoard(int amount);
	friend bool operator< (Node a, Node b);
	friend bool operator== (Node a, Node b);
};

