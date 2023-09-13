#include "Player.h"

Player::Player(const char* name, sf::Color choosedColor)
{
	m_Name  = name;
	m_Piece = choosedColor;
}

sf::Color Player::GetPlayerPiece() { return m_Piece; }

bool Player::CheckPlayerWin() { return false; }