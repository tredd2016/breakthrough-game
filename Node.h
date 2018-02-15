#pragma once

#include "GameBoard.h"
#include<vector>
#include<iostream>

using namespace std;

class GameBoard;
struct Move;

class Node {
public:

	GameBoard *gameState;
	Node *parent;
	vector<Node*> children;
	int score;	

	Node(GameBoard *g, Node *p);
	Node(GameBoard *g, Node *p, int s);
	~Node(); // Delete Recusivly 

	Node* getParent();
	void addChildren(vector<Node*> c);
	void printChildren();
	void addChild(Node* n);

	
};
