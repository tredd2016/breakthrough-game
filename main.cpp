#include "Node.h"
#include "GameBoard.h"
#include "Player.h"

#include<iostream>

using namespace std;

int main() {
	Player h1(1, 'X', true);
	Player a2(2, 'O', false);
		
	GameBoard b(h1, a2);
		
	//b.setBoardPiece(0, 0, '_');
	//b.setBoardPiece(1, 0, '_');
	//b.printBoard();

	//cout << b.activePlayer.getPlayerNum() << ": " << b.AIscore() << endl;
	//b.setActPlayer(a2);
	//cout << b.homeRowCount(a2) << endl;
	//cout << b.activePlayer.getPlayerNum() << ": " << b.AIscore() << endl;

	//b.AImakeMove(3);

	//b.printBoard();

	b.playGame();

	char ab;
	cin >> ab;

	return 0;
	
	/*
	Node *root = new Node(&b, nullptr, INT_MIN);

	Node *L1A = new Node(&b, root, INT_MIN);
	Node *L1B = new Node(&b, root, INT_MIN);
	root->children.push_back(L1A);
	root->children.push_back(L1B);


	Node *L2A = new Node(&b, L1A, INT_MIN);
	Node *L2B = new Node(&b, L1A, INT_MIN);
	L1A->children.push_back(L2A);
	L1A->children.push_back(L2B);

	Node *L2C = new Node(&b, L1B, INT_MIN);
	Node *L2D = new Node(&b, L1B, INT_MIN);
	L1B->children.push_back(L2C);
	L1B->children.push_back(L2D);


	
	Node *L3A = new Node(&b, L2A, 10);
	Node *L3B = new Node(&b, L2A, 5);
	L2A->children.push_back(L3A);
	L2A->children.push_back(L3B);

	Node *L3C = new Node(&b, L2B, -10);	
	L2B->children.push_back(L3C);
	
	Node *L3D = new Node(&b, L2C, 5);
	Node *L3E = new Node(&b, L2C, -100);
	L2C->children.push_back(L3D);
	L2C->children.push_back(L3E);

	Node *L3F = new Node(&b, L2D, -7);	
	L2D->children.push_back(L3F);
	

	cout << b.negamax(root, 3, -1) << endl;

	cout << "Result: " << root->score << endl;
	
	for (int i = 0; i < root->children.size(); ++i) {
		cout << "i: " << i << "\t" << root->children[i]->score << endl;
	}

	char ab;
	cin >> ab;

	return 0;
	*/
}