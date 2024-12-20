#include "Player.h"

Player::Player(const char color) {
	if (color != WHITE && color != BLACK) {
		this->_haveError = true;
		this->_color = NONE;
	}
	else {
		this->_haveError = false;
		this->_color = color;
	}
}

Player::Player() {
	this->_color = NONE;
	this->_haveError = true;
}

bool Player::isValidPlayer() const noexcept {
	return !this->_haveError;
}

char Player::getColor() const noexcept{
	return this->_color;
}