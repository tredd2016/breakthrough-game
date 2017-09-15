#pragma once

#include<iostream> // need this even?

using namespace std; // need this?

class Player {
public:
	//Constructor
	Player() {}
	Player(int i, char c, bool h);
	Player(const Player& p);

	//Member functions
	int getPlayerNum() const;
	char getPlayerPiece() const;
	char getOppPiece();

	void setPlayerNum(int i);
	void setPlayerPiece(char c);

	bool isHumanPlayer();

protected:
	int playerNum;
	char playerPiece;
	bool isHuman;
};
