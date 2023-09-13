#pragma once
#include "Shape.h"
#include "SFML/Graphics/CircleShape.hpp"

class Piece : public Shape
{
public:
	void Init(float xPos, float yPos, float radius);
	void UpdateColor(sf::Color newColor);

	bool InRange(int x, int y) override;
	bool InColumn(int x);
	bool IsFilled();

	sf::CircleShape GetShape();

	sf::Color GetFillColor();

private:
	float m_Radius, m_XPos, m_YPos;

	sf::CircleShape m_Shape;

	sf::Color m_IsFreeColor = sf::Color::Green;
};