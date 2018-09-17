#pragma once
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;



class Board
{
public:
	// vars
	vector<vector<int>> board;
	// functions
	Board();
	Board(vector<vector<int>> newBoard);
	~Board();
	void setBoard(vector<vector<int>> newBoard);
	vector<vector<int>> getBoard();
	int getManhattan(vector<vector<int>> goal);
	void makeMove(int dir);
	tuple<int, int> getSpace();
	void displayBoard();
	vector<int> getValidMoves();
	friend bool operator== (Board a, Board b);
};

