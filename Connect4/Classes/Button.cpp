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

	m_WasInit = true;
}

// Check if the button was already init
bool Button::CheckWasInit()
{
	return m_WasInit;
}

// Get the height of the button
float Button::GetHeight()
{
	return m_Height;
}

// Get the with of the button
float Button::GetWidth()
{
	return m_Width;
}

// Get the top left position of the button in the x axis
float Button::GetTopLeftXPos()
{
	return m_XPos;
}

// Get the top left position of the button in the Y axis
float Button::GetTopLeftYPos()
{
	return m_YPos;
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