#include "Node.h"
#include "GameBoard.h"
#include "Player.h"

#include<iostream>

using namespace std;

int main() {
	Player h1(1, 'X', true);
	Player a2(2, 'O', false);
		
	GameBoard b(h1, a2);

	//GameBoard a(h1, a2);
	
	/*
	b.setBoardPiece(6, 2, '_');
	b.setBoardPiece(4, 2, 'X');

	b.setBoardPiece(7, 5, '_');
	b.setBoardPiece(7, 7, '_');
	b.setBoardPiece(6, 6, '_');

	b.setBoardPiece(6, 7, 'X');
	b.setBoardPiece(1, 3, '_');

	b.setBoardPiece(5, 7, 'O');
	*/
	//cout << a.prevMove.coulmPosition << endl;
	//a.makeMove();
	//cout << "COLM: " << a.prevMove.coulmPosition << "\t ROW: " << a.prevMove.rowPosition << "\t DIR: " << a.prevMove.direction << endl;

	b.playGame();
	char ab;
	cin >> ab;
	return 0;
	
	/*
	Node *root = new Node(&b, nullptr);
	/////////////////////////////////////////////////////
	Node *level_1_nodeA = new Node(&b, root, 0);
	root->children.push_back(level_1_nodeA);
	Node *level_1_nodeB = new Node(&b, root, 0);
	root->children.push_back(level_1_nodeB);
	/////////////////////////////////////////////////////
	Node *level_2_nodeA = new Node(&b, level_1_nodeA, 10);
	level_1_nodeA->children.push_back(level_2_nodeA);
	Node *level_2_nodeB = new Node(&b, level_1_nodeA, -10);
	level_1_nodeA->children.push_back(level_2_nodeB);

	Node *level_2_nodeC = new Node(&b, level_1_nodeB, 5);
	level_1_nodeB->children.push_back(level_2_nodeC);
	Node *level_2_nodeD = new Node(&b, level_1_nodeB, -7);
	level_1_nodeB->children.push_back(level_2_nodeD);
	*/

	/////////////////////////////////////////////////////
	/*
	Node *level_3_nodeA = new Node(&b, level_2_nodeA, 10);
	level_2_nodeA->children.push_back(level_3_nodeA);
	Node *level_3_nodeB = new Node(&b, level_2_nodeA, 1000);
	level_2_nodeA->children.push_back(level_3_nodeB);

	Node *level_3_nodeC = new Node(&b, level_2_nodeB, -10);
	level_2_nodeB->children.push_back(level_3_nodeC);
	Node *level_3_nodeD = new Node(&b, level_2_nodeB, -100);
	level_2_nodeB->children.push_back(level_3_nodeD);

	Node *level_3_nodeE = new Node(&b, level_2_nodeC, 5);
	level_2_nodeC->children.push_back(level_3_nodeE);
	Node *level_3_nodeF = new Node(&b, level_2_nodeC, -999);
	level_2_nodeC->children.push_back(level_3_nodeF);

	Node *level_3_nodeG = new Node(&b, level_2_nodeD, -7);
	level_2_nodeD->children.push_back(level_3_nodeG);
	Node *level_3_nodeH = new Node(&b, level_2_nodeD, -20);
	level_2_nodeD->children.push_back(level_3_nodeH);
	*/

	/*
	b.negamax(root, 2, 1);
	cout << "Root value: " << root->score << endl;
	for (int i = 0; i < root->children.size(); ++i) {
		cout << i << " value: " << root->children[i]->score << endl;
	}

	
	char ab;
	cin >> ab;
	return 0;
	*/

}


/*
Node *sam = new Node(&b, nullptr);
//int ad = b.AIscore(sam);
b.printBoard();
Move m(6, 0, 'f');
b.makeMove(m);
cout << b.prevMove.rowPosition << "\t" << b.prevMove.coulmPosition << "\t" << b.prevMove.direction << endl;
b.changeTurn();

b.printBoard();

b.makeMove();
cout << b.prevMove.rowPosition << "\t" << b.prevMove.coulmPosition << "\t" << b.prevMove.direction << endl;
b.changeTurn();
b.printBoard();
//Node *root = new Node(&b, nullptr);

//int abc = b.AIscore(root);

for (int i = 0; i < root->children.size(); ++i) {
cout << root->children[i]->gameState->prevMove.rowPosition << '\t' << root->children[i]->gameState->prevMove.coulmPosition << '\t' << root->children[i]->gameState->prevMove.direction << endl;
}


*/



/*
b.setBoardPiece(6, 2, '_');
b.setBoardPiece(4, 2, 'X');

b.setBoardPiece(3, 3, 'O');
b.setBoardPiece(1, 3, '_');
b.printBoard();

b.changeTurn();
b.AImakeMove(2);
b.printBoard();
//cout << "AIScore(): " << b.AIscore() << endl;
*/