#include "Piece.h"

void Piece::Init(float xPos, float yPos, float radius)
{
	m_Shape.setRadius(radius);
	m_Shape.setOrigin(xPos, yPos);
	m_Shape.setFillColor(m_Color);

	m_XPos   = -xPos;
	m_YPos   = -yPos;
	m_Radius = radius;
}

bool Piece::InRange(int x, int y) 
{
	return (x >= m_XPos && x <= m_XPos + (m_Radius * 2)) && (y >= m_YPos && y <= m_YPos + (m_Radius * 2));
}

void Piece::UpdateColor(sf::Color newColor)
{
	m_Shape.setFillColor(newColor);
}

sf::CircleShape Piece::GetShape() { return m_Shape; }