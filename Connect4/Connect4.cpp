#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Classes/Button.h"

enum class State
{
    InMenu, InGame, InHighScores, Quit
};

//--- Global Variables ---//

State state = State::InMenu; // Set the initial state value to In Menu

//--- Connect4 Functions ---//

void menu(sf::RenderWindow &window, sf::Font textFont)
{ 
    // Set the text variables
    Button play(120.f, 50.f, -480.f, -215.f, sf::Color::Blue, "Play", -525.f, -230.f, textFont),
        highScores(140.f, 50.f, -470.f, -275.f, sf::Color::Magenta, "High Scores", -493.f, -288.f, textFont),
        quit(120.f, 50.f, -480.f, -335.f, sf::Color::Red, "Quit", -525.f, -348.f, textFont);

    while (state == State::InMenu)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type)
            {
                case sf::Event::Closed:
                    state = State::Quit;
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // Draw the buttons background
        window.draw(play.GetShape());
        window.draw(highScores.GetShape());
        window.draw(quit.GetShape());

        // Draw the text informations
        window.draw(play.GetText());
        window.draw(highScores.GetText());
        window.draw(quit.GetText());

        // end the current frame
        window.display();
    }
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1080, 600), "Connect4 Menu");

    // Set the predefined font
    sf::Font font;
    font.loadFromFile("Assets/Fonts/Roboto/Roboto-Medium.ttf");

    while (state != State::Quit)
    {
        switch (state)
        {
            case State::InMenu:
                menu(window, font);
                break;
            case State::InGame:
                break;
            case State::InHighScores:
                break;
            case State::Quit:
                break;
            default:
                break;
        }
    }

    window.close();

    return 0;
}