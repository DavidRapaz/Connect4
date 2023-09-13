#pragma once
#include "SFML/Graphics/Color.hpp";

class Player
{
public:
	Player(const char* name, sf::Color choosedColor);

	bool CheckPlayerWin();

	sf::Color GetPlayerPiece();
private:
	const char* m_Name;

	sf::Color m_Piece;
};