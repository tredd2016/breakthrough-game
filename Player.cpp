#include "Player.h"

Player::Player(int i, char c, bool h) {
	playerNum = i;
	playerPiece = c;
	isHuman = h;
}

Player::Player(const Player& p) {
	playerNum = p.playerNum;
	playerPiece = p.playerPiece;
	isHuman = p.isHuman;
}


int Player::getPlayerNum() const {
	return playerNum;
}

char Player::getPlayerPiece() const {
	return playerPiece;
}

//Not super safe
char Player::getOppPiece() {
	if (playerPiece == 'X') return 'O';
	else return 'X';
}

void Player::setPlayerNum(int i) {
	playerNum = i;
}

void Player::setPlayerPiece(char c) {
	playerPiece = c;
}

bool Player::isHumanPlayer() {
	if (isHuman) return true;
	else return false;
}
