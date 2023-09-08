#include <SFML/Graphics.hpp>
#include "Classes/Button.h"

enum class State
{
    InMenu, InGame, InHighScores, Quit
};

//--- Global Variables ---//

State state = State::InMenu; // Set the initial state value to In Menu

Button play, highScores, quit;
float pressedX, pressedY;

//--- Menu Functions ---//

void drawMenu(sf::RenderWindow& window)
{
    // Draw play button
    window.draw(play.GetShape());
    window.draw(play.GetText());

    // Draw high scores button
    window.draw(highScores.GetShape());
    window.draw(highScores.GetText());

    // Draw quit button
    window.draw(quit.GetShape());
    window.draw(quit.GetText());
}

//--- Game Functions ---//

void drawGame(sf::RenderWindow& window)
{
    window.draw(play.GetShape());
}

//--- High Scores Functions ---//

void drawHighScores(sf::RenderWindow& window)
{
    window.draw(quit.GetShape());
}

//--- Global Functions ---//

bool wasButtonPressed(Button& button)
{
    float leftTopXPos = -button.GetTopLeftXPos(),
        rightTopXPos  = button.GetWidth() + leftTopXPos,
        TopYPos       = -button.GetTopLeftYPos(),
        BottomYPos    = TopYPos + button.GetHeight();

    return (pressedX >= leftTopXPos && pressedX <= rightTopXPos) && (pressedY >= TopYPos && pressedY <= BottomYPos);
}

void handleButtonPressed()
{
    switch (state)
    {
        case State::InMenu:
            if (wasButtonPressed(play)) state = State::InGame;
            if (wasButtonPressed(highScores)) state = State::InHighScores;
            if (wasButtonPressed(quit)) state = State::Quit;

            break;
        case State::InGame:
            break;
        case State::InHighScores:
            break;
    }
}

//--- Main ---//

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1080, 600), "Connect4 Menu");

    // Set the predefined font
    sf::Font font;
    font.loadFromFile("Assets/Fonts/Roboto/Roboto-Medium.ttf");

    while (state != State::Quit)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    pressedX = event.mouseButton.x;
                    pressedY = event.mouseButton.y;
                    
                    handleButtonPressed();
                    break;
                default:
                    break;
            }
            // Handle events
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);
        
        // Draw here
        switch (state)
        {
            case State::InMenu:
                if (!play.CheckWasInit()) 
                    play.Init(120.f, 50.f, -480.f, -215.f, sf::Color::Blue, "Play", -525.f, -230.f, font);
                
                if (!highScores.CheckWasInit()) 
                    highScores.Init(140.f, 50.f, -470.f, -275.f, sf::Color::Magenta, "High Scores", -493.f, -288.f, font);
                
                if (!quit.CheckWasInit()) 
                    quit.Init(120.f, 50.f, -480.f, -335.f, sf::Color::Red, "Quit", -525.f, -348.f, font);

                drawMenu(window);
                break;
            case State::InGame:
                drawGame(window);
                break;
            case State::InHighScores:
                drawHighScores(window);
                break;
        }

        // end the current frame
        window.display();
    }

    window.close();

    return 0;
}