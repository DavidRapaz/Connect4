#pragma once
#include "Shape.h";
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Button : public Shape
{
	public:
		void Init(
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

		bool CheckWasInit();
		bool InRange(int x, int y) override;
		
		sf::RectangleShape GetShape();
		sf::Text GetText();

	private:
		float m_Width, m_Height;
		
		bool m_WasInit = false;

		sf::Text m_Description;
		sf::RectangleShape m_Shape;
};