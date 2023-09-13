#include <SFML/Graphics.hpp>
#include "Classes/Player.h"
#include "Classes/Button.h"
#include "Classes/Piece.h"

enum class State : char
{
    InMenu, InGame, InHighScores, Quit
};

enum class Turn : char
{
    PlayerOne = 1, PlayerTwo
};

//--- Global Variables ---//

State state  = State::InMenu, // Set the initial state value to In Menu
    previous = State::InMenu; 

Turn playerTurn = Turn::PlayerOne;

Button play, highScores, quit;

constexpr int WINDOW_WIDTH  = 1080; // Width of the window in pixels
constexpr int WINDOW_HEIGHT = 600;  // Height of the window in pixels

constexpr int BOARD_WIDTH  = 700; // Height of the board in pixels
constexpr int BOARD_HEIGHT = 600; // Width of the board in pixels

constexpr short BOARD_ROWS    = 6; // Total of rows
constexpr short BOARD_COLUMNS = 7; // Total of columns

float pressedX, pressedY; // store X and Y coordenates when the users presses the mouse button on the window

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

    float marginLeft = (WINDOW_WIDTH - BOARD_WIDTH) / 2;

    for (int row = 0; row < BOARD_ROWS; row++)
    {
        int offset = row * BOARD_COLUMNS;

        for (int column = 0; column < BOARD_COLUMNS; column++)
        {
            // TODO
            // Create a solution to change the radius and the position of the pieces
            // considering the height and width of the screen
            board[offset + column].Init(-marginLeft - (column * 100.f), -100.f * row, 50.f);
        }
    }
}

void drawGame(sf::RenderWindow& window, Piece* board)
{
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        int offset = row * BOARD_COLUMNS;

        for (int column = 0; column < BOARD_COLUMNS; column++)
        {
            window.draw(board[offset + column].GetShape());
        }
    }
}

bool IsWinner(Player* player, Piece* board)
{
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        int offset = row * BOARD_COLUMNS;

        for (int column = 0; column < BOARD_COLUMNS; column++)
        {

        }
    }
}

//--- High Scores Functions ---//

void drawHighScores(sf::RenderWindow& window)
{
    window.draw(quit.GetShape());
}

//--- Global Functions ---//

void handleButtonPressed(Piece* board = nullptr, Player* player = nullptr, Turn newTurn = Turn::PlayerOne)
{
    switch (state)
    {
    case State::InMenu:
        if (play.InRange(pressedX, pressedY)) state = State::InGame;
        if (highScores.InRange(pressedX, pressedY)) state = State::InHighScores;
        if (quit.InRange(pressedX, pressedY)) state = State::Quit;

        break;
    case State::InGame:
    {
        short targetCol = -1;

        // Get the target column
        for (short column = 0; column < BOARD_COLUMNS; column++)
        {
            if (board[column].InColumn(pressedX))
                targetCol = column;
        }

        // If the target column is null then avoid doing the rest of the operation
        if (targetCol == NULL) return;

        // Store the index of the array to update the piece
        short indexToUpdate = -1;

        // Go through each row
        for (short row = 0; row < BOARD_ROWS; row++)
        {
            bool currentIsFilled = board[row * BOARD_COLUMNS + targetCol].IsFilled();

            // Give the current index if it's not filled
            if (!currentIsFilled)
            {
                indexToUpdate = row * BOARD_COLUMNS + targetCol;
            }
        }

        if (indexToUpdate != -1)
        {
            board[indexToUpdate].UpdateColor(player->GetPlayerPiece());
            playerTurn = newTurn;
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Connect4 Menu");

    // Set the predefined font
    sf::Font font;
    font.loadFromFile("Assets/Fonts/Roboto/Roboto-Medium.ttf");

    // Initialize the board
    Piece* board = nullptr;

    // Initialize the players
    Player* playerOne = nullptr;
    Player* playerTwo = nullptr;

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
                    
                handleButtonPressed(
                    board, 
                    playerTurn == Turn::PlayerOne ? playerOne : playerTwo, 
                    playerTurn == Turn::PlayerOne ? Turn::PlayerTwo : Turn::PlayerOne
                );

                if (IsWinner(playerOne, board)) 
                    return;

                if (IsWinner(playerTwo, board))
                    return;
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
            if (board == nullptr)
                board = new Piece[BOARD_ROWS * BOARD_COLUMNS];

            if (playerOne == nullptr)
                playerOne = new Player("player one", sf::Color::Yellow);

            if (playerTwo == nullptr)
                playerTwo = new Player("player two", sf::Color::Red);

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