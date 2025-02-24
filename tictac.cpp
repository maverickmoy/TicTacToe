#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Requirments:
// 1. Implement a 3x3 Tic-Tac-Toe board game
// The board is represented by a 2D array that starts with all empty spaces
// The board is displayed as a 3x3 grid with each cell containing either an X, O, or empty space
// 2. Alternate turns between two players (X and O).
// 3a. Prompt the user for input on their move in the format of row (1,2 or 3) and column (letter A, B or C) of the move: e.g. row, column = 2B. get 1 char at a time
// 3b. check for valid and invalid input (# > 3, Letter > C) and invalid moves (e.g., preventing players from moving to an already occupied space).
// 4. Display the game board after each move.
// 5a. Check for a winner or a tie after each move.
// 5b. If the game is not over, switch players and continue the game at step 3.
// 6. Implement a function to reset the game board.
// 6. Allow players to play multiple rounds of the game, looping until the players decide to quit.
// 7. Display the final score of the game after each round.

// check if input is valid
bool isValidInput(vector<vector<char> > board, string input)
{
    if (input.length() != 2)
        return false;
    if (input[0] < '1' || input[0] > '3')
        return false;
    if (input[1] < 'A' || input[1] > 'C')
        return false;
    return true;
}

// convert input to row and column
void convertInput(vector<vector<char> > &board, char player, string input, int &row, int &col)
{
    row = input[0] - '1';
    col = input[1] - 'A';
}

// check if move is valid
// valid, space is empty
bool isValidMove(vector<vector<char> > board, int row, int col)
{
    // cout << "row: " << row << " col: " << col << "= " << board[row][col] << endl;
    if (board[row][col] == ' ')
        return true;
    return false;
}

void printBoard(vector<vector<char> > board)
{
    cout << endl << "  A B C" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << "|";
        }
        cout << endl;
        if (i < 2)
            cout << "  -----" << endl;
    }
}

// update Board with player move
void updateBoard(vector<vector<char> > &board, char player, int row, int col)
{
    board[row][col] = player;
}

// get input from user
void getInput(vector<vector<char> > &board, char player)
{
    string input;
    int row, col;
    bool validInput = false;
    bool validMove = false;

    do
    {
        cout << "Player " << player << ", enter your move (row, column): ";
        cin >> input;
        if (isValidInput(board, input))
        {
            convertInput(board, player, input, row, col);
            if (isValidMove(board, row, col))
            {
                validMove = true;
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Try again." << endl;
        }
    } while (!validMove);
    updateBoard(board, player, row, col);
}

bool checkWinner(vector<vector<char> > board, char player)
{
    // check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }
    }
    // check columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
        {
            return true;
        }
    }
    // check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }
    return false;
}

// check for tie, i.e., no empty spaces left
bool checkTie(vector<vector<char> > board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

// bool checkContinue();

void resetBoard(vector<vector<char> > &board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
            // cout << i << j << endl;
        }
    }
}

// random move to any blank space
void easyAI(vector<vector<char> > &board, char player)
{
    int row, col;
    bool validMove = false;

    do
    {
        row = rand() % 3;
        col = rand() % 3;
        if (isValidMove(board, row, col))
        {
            validMove = true;
        }
    } while (!validMove);
    updateBoard(board, player, row, col);
}

int main()
{
    vector<vector<char> > board(3, vector<char>(3, ' '));
    bool playAgain = false;
    char userInput;

    do {
        // print the board
        printBoard(board);
        do
        {
            // get input from player 1
            getInput(board, 'X');
            // check for winner
            printBoard(board);
            if (checkWinner(board, 'X'))
            {
                cout << "Player X wins!" << endl;
                break;
            }
            // check for tie
            if (checkTie(board))
            {
                cout << "It's a tie!" << endl;
                break;
            }

            // get input from player 2
            // Player O is AI
            easyAI(board, 'O');
            // getInput(board, 'O');
            // check for winner
            printBoard(board);
            if (checkWinner(board, 'O'))
            {
                cout << "Player O wins!" << endl;
                break;
            }
            // // check for tie
            if (checkTie(board)) {
                cout << "It's a tie!" << endl;
                break;
            }
            // print the board

        } while (true);

        // Game over: ask to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> userInput;
        if (userInput == 'y')
        {
            resetBoard(board);
            playAgain = true;
        }
        else
        {
            playAgain = false;
        }

    } while (playAgain);


    cout << "Thanks for playing!" << endl;

    return 0;
}