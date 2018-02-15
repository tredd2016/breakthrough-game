#pragma once

#include "Player.h"
#include "Node.h"
#include<iostream>
#include<string>
#include<sstream>
#include<cctype>
#include<cmath>
#include<random>
#include<regex>
#include<climits>

using namespace std;

class Node;

struct Tile {
	int rowPosition;
	int coulmPosition;

	Tile(int r, int c) : rowPosition(r), coulmPosition(c) {}
};

struct Move {
	int rowPosition;
	int coulmPosition;
	char direction; // f - forward , l - left, r - right
	//int score;

	Move() {}
	Move(int r, int c, char d) : rowPosition(r), coulmPosition(c), direction(d) {}
};

class GameBoard {
	// todo: find a way to make the board private
public:
	char Board[8][8];
	Player activePlayer, passivePlayer;
	Move prevMove; // Can make a stack to implement undo

	GameBoard();
	GameBoard(Player p1, Player p2); // Constructor 2 player
									 //GameBoard(Player p1, AIPlayer p2); // Constructor - human v AI
	GameBoard(const GameBoard& b); // Copy Constuctor

								   //Overloaded operators
	friend ostream& operator<<(ostream& os, const GameBoard& b);

	//Member functions
	void printBoard();
	void initBoard();

	void setActPlayer(Player p);
	Player getActPlayer(); 
	void setPassivePlayer(Player p);
	Player getPassivePlayer();
	void changeTurn();


	void setBoardPiece(int rowPos, int coulmPos, char playPiece);
	Tile calcMove(Move m);

	void makeMove();
	void makeMove(Move m);

	bool isValidMove(Move m);
	bool isGG();
	Move getMove();

	//AI Moves ------------------------------
	vector<Move> AIAllMoves();
	void AImakeMove(int depth);
	void buildLevel(Node *n);
	void buildTree(Node* n, int depth);
	bool isOneAway();
	int AIscore();
	int minimax(Node *root, int depth, bool maxPlayer);
	int negamax(Node *node, int depth, int POV);
	
	//---------------------------------------
	void playGame();
};