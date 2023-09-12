#include <SFML/Graphics.hpp>
#include "Classes/Button.h"
#include "Classes/Piece.h"

enum class State
{
    InMenu, InGame, InHighScores, Quit
};

//--- Global Variables ---//

State state  = State::InMenu, // Set the initial state value to In Menu
    previous = State::InMenu;

Button play, highScores, quit;

constexpr int SCREEN_WIDHT  = 1080;
constexpr int SCREEN_HEIGHT = 600;

constexpr short BOARD_HEIGHT = 6; // Total of rows
constexpr short BOARD_WIDTH  = 7; // Total of columns

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

void initGameState(Piece* board, bool redraw = false)
{
    if (previous == State::InGame && !redraw) return;

    previous = State::InGame;

    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        int offset = row * BOARD_WIDTH;

        for (int column = 0; column < BOARD_WIDTH; column++)
        {
            // TODO
            // Create a solution to change the radius and the position of the pieces
            // considering the height and width of the screen
            board[offset + column].Init(-154.29 * column, -100.f * row, 50.f);
        }
    }
}

void drawGame(sf::RenderWindow& window, Piece* board)
{
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        int offset = row * BOARD_WIDTH;

        for (int column = 0; column < BOARD_WIDTH; column++)
        {
            window.draw(board[offset + column].GetShape());
        }
    }
}

//--- High Scores Functions ---//

void drawHighScores(sf::RenderWindow& window)
{
    window.draw(quit.GetShape());
}

//--- Global Functions ---//

void handleButtonPressed(Piece* board = NULL)
{
    switch (state)
    {
    case State::InMenu:
        if (play.InRange(pressedX, pressedY)) state = State::InGame;
        if (highScores.InRange(pressedX, pressedY)) state = State::InHighScores;
        if (quit.InRange(pressedX, pressedY)) state = State::Quit;

        break;
    case State::InGame:
        for (int row = 0; row < BOARD_HEIGHT; row++)
        {
            int offset = row * BOARD_WIDTH;

            for (int column = 0; column < BOARD_WIDTH; column++)
            {
                if(board[offset + column].InRange(pressedX, pressedY))
                    board[offset + column].UpdateColor(sf::Color::Blue);
            }
        }
        break;
    case State::InHighScores:
        break;
    }
}

//--- Main ---//

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "Connect4 Menu");

    // Set the predefined font
    sf::Font font;
    font.loadFromFile("Assets/Fonts/Roboto/Roboto-Medium.ttf");

    Piece* board = new Piece[BOARD_HEIGHT * BOARD_WIDTH];

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
                    
                handleButtonPressed(board);
                break;
            case sf::Event::Closed:
                state = State::Quit;
                break;
            }
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
            initGameState(board);
            drawGame(window, board);
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