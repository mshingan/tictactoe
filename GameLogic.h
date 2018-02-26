#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <string> 

using namespace std;

int const BOARD_ROWS=3 ; 
int const BOARD_COLS=3;
class GameLogic{
    public:
        GameLogic();
        void change_turn(); //changes the turn 
        char get_turn(); //gets the turn of the player
        int get_col(); //converts char col into int
        int get_row(); //converts char row into int 
        void set_position(string pos); // sets the position of the row and column
        void show_board(); //prints the board
        void updateboard(); // updates the board
        bool three_in_row(char player); // checks if there are 3 of same player in row
        bool three_in_col(char player); // checks if there are 3 of same player in col
        bool three_diagonal(char player); // checks if there 3 of same player in diagonal 
        bool check_win(char player); //checks to see if there is a winner on the board
        bool is_valid_row(int r); // checks if the row inputed by the user is valid
        bool is_valid_col(int c); //checks if the column inputed by the user is valid 
        bool two_in_row(char player); //checks if there are two of same player in row and puts and O there
        bool two_in_col(char player); //checks if there are two of the same player in the same column
        bool two_diagonal(char player); //checks if there are two of the same player in the diagonal 
        bool attack(); // if there are two O's on the board then place in O in the winning spot
        bool defend(); // if there are two X's on the board. then place an O in the spot that stops X from winning 
        bool move();  //if there aren't two O's or two X's O simply makes a move
        void play(); // plays the game
        
    private: 
        bool gameOver;  //boolean that is true if game is over, false if it isn't
        char turn; //char that holds current turn
        char row; //row inputed
        char col; //column inputed
        int r; // int version of row
        int c; // int version of col 
        char firstMove; //finds first move of player
        char board[3][3]; //array that contains game board information
        
};
#endif