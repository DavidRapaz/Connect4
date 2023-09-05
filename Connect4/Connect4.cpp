#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

enum State
{
    StateInMenu, StateInGame, StateInHighScores, StateQuit
};

//--- Global Variables ---//

State state = StateInMenu; // Set the initial state value to In Menu

//--- Connect4 Functions ---//

void game()
{

}

void menu(sf::RenderWindow &window, sf::Font &font)
{ 
    // Set the text variables
    sf::Text playText,
        highScoreText,
        quitText,
        text;

    // Define the font to use
    playText.setFont(font);
    highScoreText.setFont(font);
    quitText.setFont(font);

    // Set the text
    playText.setString("Play");
    highScoreText.setString("High Scores");
    quitText.setString("Quit");

    // Set the Color
    playText.setFillColor(sf::Color::Red);
    highScoreText.setFillColor(sf::Color::White);
    quitText.setFillColor(sf::Color::White);

    // Set the size
    playText.setCharacterSize(18);
    highScoreText.setCharacterSize(18);
    quitText.setCharacterSize(18);

    // Set position
    playText.setOrigin(-525.f, -230.f);
    highScoreText.setOrigin(-493.f, -288.f);
    quitText.setOrigin(-525.f, -348.f);

    // Define the buttons shape and sizes
    sf::RectangleShape playGame(sf::Vector2f(120.f, 50.f)),
        highScores(sf::Vector2f(140.f, 50.f)),
        quitGame(sf::Vector2f(120.f, 50.f));

    // Define the buttons colors
    playGame.setFillColor(sf::Color::Cyan);
    highScores.setFillColor(sf::Color::Magenta);
    quitGame.setFillColor(sf::Color::Red);

    // Define the buttons origin point
    playGame.setOrigin(-480.f, -215.f);
    highScores.setOrigin(-470.f, -275.f);
    quitGame.setOrigin(-480.f, -335.f);

    while (state == StateInMenu)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            switch (event.type)
            {
                case sf::Event::Closed:
                    state = StateQuit;
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    break;
                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // Draw the buttons background
        window.draw(playGame);
        window.draw(highScores);
        window.draw(quitGame);

        // Draw the text informations
        window.draw(playText);
        window.draw(highScoreText);
        window.draw(quitText);

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

    while (state != StateQuit)
    {
        switch (state)
        {
            case StateInMenu:
                menu(window, font);
                break;
            case StateInGame:
                break;
            case StateInHighScores:
                break;
            case StateQuit:
                break;
            default:
                break;
        }
    }

    return 0;
}