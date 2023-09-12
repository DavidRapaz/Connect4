#pragma once
#include <SFML/Graphics/Color.hpp>

class Shape
{
public:
	virtual bool InRange(int x, int y) = 0;

protected:
	float m_LeftXPos, m_RightXPos, m_TopYPos, m_BottomYPos;
};