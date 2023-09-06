#include "Button.h"

// Initialize the button
Button::Button(
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
	m_Width  = width;
	m_Height = height;
	m_XPos   = xPos;
	m_YPos   = yPos;

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