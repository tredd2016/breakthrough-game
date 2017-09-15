#include "Node.h"

Node::Node(GameBoard *g, Node *p) {
	parent = p;
	gameState = g;
	//score = -1;
}

Node::Node(GameBoard *g, Node *p, int s) {
	parent = p;
	gameState = g;
	score = s;
}


Node::~Node() {	
	if (children.empty()) {
		delete[] gameState;
		children.clear();
	}
	else {
		for (size_t i = 0; i < children.size(); ++i) {
			delete(children[i]);
		}
		
	}
}

Node* Node::getParent() {
	return parent;
}

void Node::addChildren(vector<Node*> c) {
	children = c;
}

void Node::addChild(Node* n) {
	children.push_back(n);
}


//Shouldn't actually need this, handle it in GameBoard where the function declared to avoid circular dependency
void Node::printChildren() {
	for (size_t i = 0; i < children.size(); ++i) {
		cout << "Gameboard: " << i + 1 << endl;
		//children[i]->board.printBoard();
		//cout << children[i]->board; 
	}
}

