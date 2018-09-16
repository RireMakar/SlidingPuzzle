#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include "Board.h"
#include <time.h>

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
	void shuffleBoard(int amount);
};

