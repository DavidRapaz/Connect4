#include <SFML/Graphics.hpp>
#include "Classes/Player.h"
#include "Classes/Button.h"
#include "Classes/Piece.h"

enum class State : char
{
    InMenu, InGame, EndGame, Quit
};

enum class Turn : char
{
    PlayerOne = 1, PlayerTwo
};

//--- Global Variables ---//

State state  = State::InMenu, // Set the initial state value to In Menu
    previous = State::InMenu; 

Turn playerTurn = Turn::PlayerOne;

Button *play, *quit, *replay, *quitToMenu;

constexpr int WINDOW_WIDTH  = 1080; // Width of the window in pixels
constexpr int WINDOW_HEIGHT = 600;  // Height of the window in pixels

constexpr int BOARD_WIDTH  = 700; // Height of the board in pixels
constexpr int BOARD_HEIGHT = 600; // Width of the board in pixels

constexpr short BOARD_ROWS    = 6; // Total of rows
constexpr short BOARD_COLUMNS = 7; // Total of columns

int totalPiecesPlayed; // Used to keep track how many pieces where played allong the game

float pressedX, pressedY; // store X and Y coordenates when the users presses the mouse button on the window

//--- Menu Functions ---//

void drawMenu(sf::RenderWindow& window)
{
    // Draw play button
    window.draw(play->GetShape());
    window.draw(play->GetText());

    // Draw quit button
    window.draw(quit->GetShape());
    window.draw(quit->GetText());
}

//--- Game Functions ---//

void initGameState(Piece* board, bool redraw = false)
{
    if (previous == State::InGame) return;

    previous          = State::InGame;
    totalPiecesPlayed = 0;

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

void drawEndGame(sf::RenderWindow& window)
{
    // Draw replay button
    window.draw(replay->GetShape());
    window.draw(replay->GetText());

    // Draw quit to menu button
    window.draw(quitToMenu->GetShape());
    window.draw(quitToMenu->GetText());
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

bool isWinner(Player* player, Piece* board)
{
    // Check if in the same row
    for (int row = 0; row < BOARD_ROWS; row++)
    {
        int offset = row * BOARD_COLUMNS;

        for (int column = 0; column < BOARD_COLUMNS; column++)
        {
            int columnsRight = BOARD_COLUMNS - column; // Get how many pieces to the right are left
            int rowsBellow   = BOARD_ROWS - row; // Get how many pieces down are left
            int index        = offset + column; // Get the start index

            // Check vertically from top to bottom
            if (rowsBellow >= 4)
            {
                if (
                    board[index].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + BOARD_COLUMNS].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + BOARD_COLUMNS * 2].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + BOARD_COLUMNS * 3].GetFillColor() == player->GetPlayerPiece()
                )
                    return true;
            }

            // Check horizontally from left to right
            if (columnsRight >= 4)
            {
                if (
                    board[index].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + 1].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + 2].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + 3].GetFillColor() == player->GetPlayerPiece()
                )
                    return true;
            }

            // Check the diagonal from left to right
            if (rowsBellow >= 4 && columnsRight >= 4)
            {
                if (
                    board[index].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 1 + 1)].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 2 + 2)].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 3 + 3)].GetFillColor() == player->GetPlayerPiece()
                )
                    return true;
            }

            // Check the diagonal from right to left
            if (rowsBellow >= 4 && columnsRight <= 4)
            {
                if (
                    board[index].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 1 - 1)].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 2 - 2)].GetFillColor() == player->GetPlayerPiece() &&
                    board[index + (BOARD_COLUMNS * 3 - 3)].GetFillColor() == player->GetPlayerPiece()
                )
                    return true;
            }
        }
    }

    return false;
}

//--- Global Functions ---//

void handleButtonPressed(Piece* board = nullptr, Player* player = nullptr, Turn newTurn = Turn::PlayerOne)
{
    switch (state)
    {
    case State::InMenu:
        if (play->InRange(pressedX, pressedY)) state = State::InGame;
        if (quit->InRange(pressedX, pressedY)) state = State::Quit;

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
        if (targetCol == -1) return;

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
            
            if (isWinner(player, board))
            {
                state    = State::EndGame;
                previous = State::EndGame;
            } else
            {
                playerTurn = newTurn;
            }
        }
    }
    break;
    case State::EndGame:
        if (replay->InRange(pressedX, pressedY)) state = State::InGame;
        if (quitToMenu->InRange(pressedX, pressedY)) state = State::InMenu;
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
            if (play == nullptr) play = new Button();
            if (quit == nullptr) quit = new Button();

            if (!play->CheckWasInit()) 
                play->Init(120.f, 50.f, -480.f, -255.f, sf::Color::Blue, "Play", -525.f, -270.f, font);
                
            if (!quit->CheckWasInit()) 
                quit->Init(120.f, 50.f, -480.f, -315.f, sf::Color::Red, "Quit", -525.f, -328.f, font);

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
        case State::EndGame:
            if (replay == nullptr) replay = new Button();
            if (quitToMenu == nullptr) quitToMenu = new Button();

            if (!replay->CheckWasInit())
                replay->Init(160.f, 50.f, -480.f, -255.f, sf::Color::Black, "Play Again", -525.f, -270.f, font);

            if (!quitToMenu->CheckWasInit())
                quitToMenu->Init(160.f, 50.f, -480.f, -315.f, sf::Color::Cyan, "Quit To Menu", -505.f, -328.f, font);
            
            drawGame(window, board);
            drawEndGame(window);
            break;
        }

        // end the current frame
        window.display();
    }

    window.close();

    return 0;
}