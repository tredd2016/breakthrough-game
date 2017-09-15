#include "GameBoard.h"

GameBoard::GameBoard() {
	//default constructor...do something here
}

GameBoard::GameBoard(Player p1, Player p2) {
	activePlayer = p1;
	passivePlayer = p2;
	initBoard();
}

GameBoard::GameBoard(const GameBoard& b) {
	activePlayer = b.activePlayer;
	passivePlayer = b.passivePlayer;
	prevMove = b.prevMove; 
	//Quick hack - perhaps use memset
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Board[i][j] = b.Board[i][j];
		}
	}
}


// Simply one perspecive for now (not functional)->prints address?
ostream& operator<<(ostream& os, const GameBoard& b) {
	os << "   a b c d e f g h" << endl;
	for (int i = 0; i<8; ++i) {
		os << 8 - i << " |";
		for (int j = 0; j<8; ++j) {
			os << b.Board[i][j] << "|";
		}
		os << endl;
	}
	return os;
}


void GameBoard::initBoard() {
	for (int i = 0; i<8; ++i) {
		for (int j = 0; j<8; ++j) {
			if (i == 0 || i == 1) Board[i][j] = 'O';
			else if (i == 6 || i == 7) Board[i][j] = 'X';
			else Board[i][j] = '_';
		}
	}
}


void GameBoard::printBoard() {
	// Player 1 Board View
	if (activePlayer.getPlayerNum() == 1) {
		cout << "   a b c d e f g h" << endl;
		for (int i = 0; i<8; ++i) {
			cout << 8 - i << " |";
			for (int j = 0; j<8; ++j) {
				cout << Board[i][j] << "|";
			}
			cout << endl;
		}
	}
	// Player 2 Board View
	else {
		cout << "   h g f e d c b a" << endl;
		for (int i = 0; i<8; ++i) {
			cout << i + 1 << " |";
			for (int j = 0; j<8; ++j) {
				cout << Board[7 - i][7 - j] << "|";
			}
			cout << endl;
		}
	}
}

void GameBoard::setActPlayer(Player p) {
	activePlayer = p;
}

Player GameBoard::getActPlayer() {
	return activePlayer;
}

void GameBoard::setPassivePlayer(Player p) {
	passivePlayer = p;
}

Player GameBoard::getPassivePlayer() {
	return passivePlayer;
}


void GameBoard::changeTurn() {
	Player swap = activePlayer;
	activePlayer = passivePlayer;
	passivePlayer = swap;
}

void GameBoard::setBoardPiece(int rowPos, int coulmPos, char playPiece) {
	Board[rowPos][coulmPos] = playPiece;
}

Tile GameBoard::calcMove(Move m) {
	int parity, newRow, newCoulm = 0;

	if (activePlayer.getPlayerNum() == 1) {
		parity = -1;
	}
	else if (activePlayer.getPlayerNum() == 2) {
		parity = 1;
	}
	else {
		cout << "INVALID PLAYER NUMBER GameBoard::calcMove()" << endl;
	}
	//Forward
	if (m.direction == 'f' || m.direction == 'F') {
		newCoulm = m.coulmPosition;
		newRow = m.rowPosition + parity;
	}
	//Left
	else if (m.direction == 'l' || m.direction == 'L') {
		newCoulm = m.coulmPosition + parity;
		newRow = m.rowPosition + parity;
	}
	//Right
	else if (m.direction == 'r' || m.direction == 'R') {
		newCoulm = m.coulmPosition - parity;
		newRow = m.rowPosition + parity;
	}
	Tile dest(newRow, newCoulm);
	return dest;
}

//Move assumed to be correct from AI player
void GameBoard::makeMove(Move m) {
	Tile dest = calcMove(m);
	setBoardPiece(dest.rowPosition, dest.coulmPosition, activePlayer.getPlayerPiece());
	setBoardPiece(m.rowPosition, m.coulmPosition, '_');
	// Update the prev move
	prevMove = m;
}

//Make move from user input
void GameBoard::makeMove() {
	bool valid = false;
	while (!valid) {
		Move m = getMove();
		if (isValidMove(m)) {
			Tile dest = calcMove(m);
			// Make move
			setBoardPiece(dest.rowPosition, dest.coulmPosition, activePlayer.getPlayerPiece());
			//Replace old piece
			setBoardPiece(m.rowPosition, m.coulmPosition, '_');
			// Update the prev move
			prevMove = m;
			valid = true;
		}
		else {
			cout << endl << "Invalid move, please try again.." << endl;
			printBoard();
		}
	}
}


bool GameBoard::isValidMove(Move m) {
	// Calc proposed move destination
	Tile dest = calcMove(m);

	// Check if Player even has a piece at orgin
	if (Board[m.rowPosition][m.coulmPosition] != activePlayer.getPlayerPiece()) {
		return false;
	}
	// Check if destination is in bounds
	else if (dest.rowPosition > 7 || dest.rowPosition < 0 || dest.coulmPosition > 7 || dest.coulmPosition < 0) {
		return false;
	}
	// Check if move is attempting to jump opponents piece moving forward
	else if (m.direction == 'f' && Board[dest.rowPosition][dest.coulmPosition] == activePlayer.getOppPiece()) {
		return false;
	}
	// Check if destination is occupied by that users piece already
	else if (Board[dest.rowPosition][dest.coulmPosition] == activePlayer.getPlayerPiece()) {
		return false;
	}

	else return true;
}

Move GameBoard::getMove() {
	string usrInput;
	regex validRegex("([a-h]|[A-H])[1-8] [fFlLrR]");
	bool valid = false;
	//char inRow, dir;
	//int inCoulm = 0;

	cout << "Player " << activePlayer.getPlayerNum() << ": please enter a move" << endl;
	while (1) {
		cout << "Move: ";
		getline(cin, usrInput);
		if (regex_match(usrInput, validRegex))
			break;
		cout << "Invalid input format, please try again" << endl;
	}
	// Convert Coulm to lowercase and subtract ascii value of 'a' to get integer representation
	char coulmChar = tolower(usrInput[0]);
	int coulmInt = coulmChar - 97;

	// Convert to int - Must adjust index from board to array
	int rowInt = abs(8 - atoi(&usrInput[1]));

	// Direction, convert to lower and leave as is
	char dirChar = tolower(usrInput[3]);

	Move rtnVal(rowInt, coulmInt, dirChar);
	return rtnVal;

}

bool GameBoard::isGG() {
	for (int i = 0; i<8; ++i) {
		if (Board[0][i] == 'X') return true;
		if (Board[7][i] == 'O') return true;
	}
	return false;
}

void GameBoard::playGame() {
	while (!isGG()) {
		cout << "------------------------------------" << endl;
		printBoard();
		if (activePlayer.isHumanPlayer())			
			makeMove(); // need to fix this function naming scheme 

		else AImakeMove(4);

		changeTurn();
	}
	printBoard();
	cout << "The game is over" << endl; // Print game winner here
}

//===================================================================================================================
vector<Move> GameBoard::AIAllMoves() {
	vector<Move> allMoves;

	for (int i = 0; i<8; ++i) {
		for (int j = 0; j<8; ++j) {
			if (Board[i][j] == activePlayer.getPlayerPiece()) {
				//Try all possible moves (clean this up)
				Move f(i, j, 'f');
				Move l(i, j, 'l');
				Move r(i, j, 'r');
				if (isValidMove(f)) allMoves.push_back(f);
				if (isValidMove(l)) allMoves.push_back(l);
				if (isValidMove(r)) allMoves.push_back(r);
			}
		}
	}
	//cout << "Number of moves found: " << allMoves.size() << endl;
	return allMoves;
}

void GameBoard::AImakeMove(int depth) {
	//Build out the tree
	Node *root = new Node(this, nullptr);
	buildTree(root, depth);
	negamax(root, depth, 1);
	
	int v = INT_MIN;
	Node *var = root->children[0]; 
	for (int i = 0; i < root->children.size(); ++i) {
		cout << i << " value: " << root->children[i]->score << endl;
		if (root->children[i]->score > v) {
			v = root->children[i]->score;
			var = root->children[i];
		}
	}

	//NEED TO FETCH THE MOVE RELATED TO THE HIGHEST SCORE
	//PERHAPS NOT SAFE - SHOULD CHANGE
	for (int i = 0; i < root->children.size(); ++i) {

	}
	
	cout << "VAR: " << var->score << endl;
	cout << var->gameState->prevMove.rowPosition << "  " << var->gameState->prevMove.coulmPosition << "  " << var->gameState->prevMove.direction << endl;
	makeMove(var->gameState->prevMove);
	delete root;
}

void GameBoard::buildLevel(Node *n) {
	//get all possible moves
	vector<Move> possibleMoves = n->gameState->AIAllMoves();		
	// Make all possible moves
	for (int i = 0; i < possibleMoves.size(); ++i) {
		// Make a Gameboard to store new gamestate
		GameBoard *temp = new GameBoard(*n->gameState); // will delete[] when root node is destructed

		//Make the move 
		temp->makeMove(possibleMoves[i]);
		temp->prevMove = possibleMoves[i];

		//Calculate score of the made move
		int moveScore = temp->AIscore();
		//cout << "Move score:\t" << moveScore << endl;

		//Change game turn
		temp->changeTurn();

		//Create a new node for the move
		Node *newNode = new Node(temp, n, moveScore); // will delete[] when root node is destructed

		//Add the new node as a child
		n->children.push_back(newNode);
	}
}


void GameBoard::buildTree(Node *n, int depth) {
	if (depth == 0) return;
	else {
		buildLevel(n);
		for (int i = 0; i < n->children.size(); ++i) {
			buildTree(n->children[i], depth - 1);
		}
	}
	
}

bool GameBoard::isOneAway() {
	for (int i = 0; i < 8; ++i) {
		if (Board[1][i] == 'X') {
			// Check if piece can be stopped
			if (i == 0) {
				if (Board[0][1] == '_') return true;
				else continue; 
			}
			else if (i == 7) {
				if (Board[0][6] == '_') return true;
				else continue;
			}
			else {
				if (Board[0][i - 1] == '_' && Board[0][i + 1] == '_') return true;
				else continue;
			}
			
		}
		// Same logic for 'O'
		if (Board[6][i] == 'O') {
			if (i == 0) {
				if (Board[7][1] == '_') return true;
				else continue;
			}
			else if (i == 7) {
				if (Board[7][6] == '_') return true;
				else continue;
			}
			else {
				if (Board[7][i - 1] == '_' && Board[7][i + 1] == '_') return true;
				else continue;
			}
			
		}
	}
	return false;
}

// Need to fix all the values
int GameBoard::AIscore() {
	int score = 0; 
	int numX = 0;
	int numO = 0;
	int pieceDiff, totPiece = 0;
	// Case 1: winning? [Most signifigant digit]
	// TODO: Fix this quick hack
	if (isGG()) {		
		for (int i = 0; i < 8; ++i) {
			if (Board[0][i] == activePlayer.getPlayerPiece() || Board[7][i] == activePlayer.getPlayerPiece()) {
				score += 1000000000;
				break;
			}
			if (Board[0][i] == passivePlayer.getPlayerPiece() || Board[7][i] == passivePlayer.getPlayerPiece()) {
				score -= 1000000000;
				break;
			}
		}
	}
	
	// Case 2: One position away from winning
	//TODO: Fix this quick hack
	if (isOneAway()) {
		bool isMe = false;
		for (int i = 0; i < 8; ++i) {
			if (Board[1][i] == activePlayer.getPlayerPiece() || Board[7][i] == activePlayer.getPlayerPiece()) {
				isMe = true;
				break;
			}
		}
		if(!isMe) score += 1000000000 / 4;
		else score -= 1000000000 / 4;
	}

	// Case 3: Who has the most pieces? [Next 2 signifigant digits]
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (Board[i][j] == 'X') {
				++numX;
				++totPiece;
			}
			if (Board[i][j] == 'O') {
				++numO;
				++totPiece;
			}
		}
	}
	if (activePlayer.getPlayerPiece() == 'X') pieceDiff = numX - numO;
	else pieceDiff = numO - numX;
	pieceDiff *= 10000;
	score = score + pieceDiff;

	//Case 4: How many pieces are left? [Next 2 signifigant pieces]
	// Better if lower number of pieces if we're ahead - Worse if lower number of pieces and we're behind




	// Case 4: # of row/coulm segment left

	// Case 5: Psudo-Random number to avoid appearing deterministic
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(0, 1000000);
	int r = dis(gen) % 99;
	score = score + r;


	return score;
}

int GameBoard::minimax(Node *node, int depth, bool maxPlayer) {
	if (depth == 0 || node->children.empty()) {
		return node->score;
	}

	if (maxPlayer) {
		int bestValue = INT_MIN;
		for (int i = 0; i < node->children.size(); ++i) {
			node->children[i]->score = minimax(node->children[i], depth - 1, false);
			if (node->children[i]->score > bestValue) bestValue = node->children[i]->score;
		}
		//cout << "Maxplayer best value " << bestValue << endl;
		return bestValue;
	}

	else {
		int bestValue = INT_MAX;
		for (int i = 0; i < node->children.size(); ++i) {
			node->children[i]->score = minimax(node->children[i], depth - 1, true);
			if (node->children[i]->score < bestValue) bestValue = node->children[i]->score;
		}
		//cout << " best value " << bestValue << endl;
		return bestValue;
	}
}

int GameBoard::negamax(Node *node, int depth, int POV) {
	if (depth == 0 || node->children.empty()) return POV * node->score;
	int bestValue = INT_MIN;
	for (int i = 0; i < node->children.size(); ++i) {
		node->score = -negamax(node->children[i], depth - 1, -POV);
		if (node->score > bestValue) bestValue = node->score;
	}
	return bestValue;
}