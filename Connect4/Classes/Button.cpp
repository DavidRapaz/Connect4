#include "Button.h"

// Initialize the button
void Button::Init(
	float width, 
	float height,
	float xPos,
	float yPos,
	sf::Color bgColor, 
	const char* text,
	float textXPos,
	float textYPos,
	sf::Font &font,
	sf::Color textColor,
	int textSize
)
{
	// Set float properties for with, height, x position and y position
	m_Width      = width;
	m_Height     = height;
	m_LeftXPos   = xPos;
	m_RightXPos  = -xPos + width;
	m_TopYPos    = yPos;
	m_BottomYPos = -yPos + height;

	// Set button size and background
	m_Shape.setSize(sf::Vector2f(width, height));
	m_Shape.setFillColor(bgColor);
	m_Shape.setOrigin(xPos, yPos);

	// Set font, text, size, color and position
	m_Description.setFont(font);
	m_Description.setString(text);
	m_Description.setFillColor(textColor);
	m_Description.setCharacterSize(textSize);
	m_Description.setOrigin(textXPos, textYPos);

	m_WasInit = true;
}

// Check if the button was already init
bool Button::CheckWasInit()
{
	return m_WasInit;
}

// Check if the coords and inside the buttons range
bool Button::InRange(int x, int y)
{
	return (x >= (-m_LeftXPos) && x <= m_RightXPos) && (y >= (-m_TopYPos) && y <= m_BottomYPos);
}

// Return the shape type
sf::RectangleShape Button::GetShape()
{
	return m_Shape;
}

// Return the description text
sf::Text Button::GetText()
{
	return m_Description;
}