#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Button
{
	public:
		Button(
			float width,
			float height,
			float xPos,
			float yPos,
			sf::Color bgColor,
			const char* text,
			float textXPos,
			float textYPos,
			sf::Font &font,
			sf::Color textColor = sf::Color::White,
			int textSize = 18
		);
		sf::RectangleShape GetShape();
		sf::Text GetText();

	private:
		float m_Width, m_Height, m_XPos, m_YPos;
		sf::Text m_Description;
		sf::RectangleShape m_Shape;
};