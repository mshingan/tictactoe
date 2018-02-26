#include <string>
#include <iostream>
#include<cstdlib>
#include "GameLogic.h"

using namespace std;
/**
 * constructer that initializes the game board
 */
GameLogic::GameLogic(){
    gameOver= false;
    firstMove = ' ';
    turn = ' ';
    row = ' ';
    col = ' ';
    r=0;
    c=0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            board[i][j] = '_';
        }
    }
}

/**
 * @return turn: char that holds the current turn
 */
char GameLogic:: get_turn(){
    return turn;
}

/**
 * function that changes the current turn
 */
void GameLogic::change_turn(){
    if(turn == 'X'){
        turn = 'O';
    }
    else if(turn == 'O'){
        turn = 'X';
    }
}

/**
 * @param r: int value of row inputed
 * @return bool
 * function that checks if the inputed r is not valid, true if it is valid, false if it is not
 */
bool GameLogic::is_valid_row(int r){
    if(r<1 || r>3){
        return false;
    }
    return true;
}

/**
 * @param c: int value of column inputed
 * @return bool
 * function that returns true if the column inputed is valid
 */
bool GameLogic::is_valid_col(int c){
    if(c<1 || c>3){
        //cout<<'Y';
        return false;
    }
    return true;
}

/**
 * @param pos: string inputed by the user indicating where the user wants to place  X
 * function that sets the row equal to the first item inputed and the col to the second item inputed
 */
void GameLogic::set_position(std::string pos){
        row =  pos[0];
        col = pos[2];
}

/**
 * @return r
 * function that returns the integer value of the row
 */
int GameLogic::get_row(){
    r = row-'0';
    return r;
}

/**
 * @return c
 * function that returns the integer value of the column
 */
int GameLogic::get_col(){
    c = col-'0';
    return c;
}
/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are two of the same player in a row
 */
bool GameLogic::two_in_row(char player){
    for(int i =0; i<3; ++i){
        if(board[i][0] == player && board[i][1] == player && board[i][2] == '_'){
            board[i][2] = 'O';
            return true; 
        }
        else if(board[i][0] == '_' && board[i][1] == player && board[i][2] == player){
            board[i][0] = 'O';
            return true;
        }
        else if(board[i][0] == player && board[i][1] == '_' && board[i][2] == player){
            board[i][1] = 'O';
            return true;
        }
    }
    return false;
}

/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are two of the same player in a column
 */
bool GameLogic::two_in_col(char player){
    for(int i = 0; i<3; ++i){
        if(board[0][i] == player && board[1][i] == player&& board[2][i] == '_' ){
            board[2][i]= 'O';
            return true;
        }
        else if(board[0][i] == '_' && board[1][i] == player&& board[2][i] == player ){
            board[0][i] = 'O';
            return true;
        }
        else if(board[0][i] == player && board[1][i] == '_'&& board[2][i] == player){
            board[1][i] = 'O';
            return true;
        }
    }
    return false;
}

/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are two of the same player in a diagonal
 */
bool GameLogic:: two_diagonal(char player){
    if(board[0][0] == player && board[1][1] =='_' && board[2][2]== player){
        board[1][1] = 'O';
        return true;
    }
    else if(board[0][0] == '_' && board[1][1] ==player && board[2][2]== player){
        board[0][0] = 'O';
        return true;
    }
    else if(board[0][0] == player && board[1][1] ==player  && board[2][2]== '_'){
        board[2][2] = 'O';
        return true;
    }
    else if(board[0][2] == player && board[1][1] == '_' && board[2][0] == player){
        board[1][1] = 'O';
        return true;
    }
    else if(board[0][2] == '_' && board[1][1] == player && board[2][0] == player){
        board[0][2] = 'O';
        return true;
    }
    else if(board[0][2] == player && board[1][1] == player && board[2][0] == '_'){
        board[2][0] = 'O';
        return true;
    }
    return false;
}

/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are three of the same player in a diagonal
 */
bool GameLogic::three_diagonal(char player ){
    if(board[0][0] ==player && board[1][1] ==player && board[2][2] == player){
        return true;
    }
    else if(board[0][2] == player && board[1][1]== player && board[2][0] == player){
        return true;
    }
    return false;
}

/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are three of the same player in a row
 */
bool GameLogic::three_in_row(char player){
    for(int i=0;i<3;++i){
        if(board[i][0]==player && board[i][1] == player && board[i][2] == player){
            return true;
        }
    }
    return false;
}

/**
 * @param player: char value indicating the turn
 * @return bool
 * function that returns true if there are three of the same player in a column
 */
bool GameLogic::three_in_col(char player){
    for(int i=0;i<3;++i){
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player){
            return true;
        }
    }
    return false;
}

/**
 * @player: char value indicating the turn
 * return bool
 * function that returns true if the player has won the game
 */
bool GameLogic::check_win(char player){
    if(three_in_col(player) || three_in_row(player)|| three_diagonal(player)){
        gameOver = true;
        cout<<"Game over! "<<player<<" has won!";
        return true;
    }
    else{
        int count =0;
        for(int i=0;i<3;++i){
            for(int j=0; j<3; ++j){
                if (board[i][j] == '_' ){
                    count +=1; 
                }
            }
        }

        if(count>0){
            gameOver = false;
            //count = 0;
            return false; 
            
        }      
        else{
            cout<<"Nobody won! it's a tie!";
            gameOver = true;
            return true;
            }
        }
}
       // count =0;

/**
 * @return bool
 * function that returns true if there are two in a row of O and places an O in the winning spot
 */
bool GameLogic:: attack(){
    if(two_in_row('O')){
        return true;
    }
    else if(two_in_col('O')){
        return true;
    }
    else if(two_diagonal('O')){
        return true;
    }
    return false;
}

/**
 * @return bool
 * function that returns true if there are two of X in a row and places an X in the winning spot
 */
bool GameLogic:: defend(){
    if(two_in_row('X')){
        return true;
    }
    else if(two_in_col('X')){
        return true;
    }
    else if(two_diagonal('X')){
        return true;
    }
    return false;
    
}
/**
 * @return bool
 * function that places an O on the board 
 */
bool GameLogic:: move(){

    bool flag= false;
    if(firstMove == 'O'){
        if(board[0][0] == '_'){
            board[0][0] = 'O';
            return true;
            }
            
        
        else if (board[1][1] == '_'){
            board[1][1]= 'O';
            return true;
        //check_win(get_turn());
        //change_turn();
        }
    }
    else if (board[1][1] == '_'){
        board[1][1]= 'O';
        return true;
    }
    else if(board[2][0] == '_'){
        board[2][0] = 'O';
        return true;
        //check_win(get_turn());
        //change_turn();
    }
    else{
        for(int i =0; i<3; ++i){
            for(int j= 0; j<3; ++j){
                if(board[i][j] == '_'){
                    board[i][j] = get_turn();
                    flag = true;
                    break;
                }
                if(flag){break;}
            }
            if(flag){break;};
        }
    return true;
    }
    return false;
    
}

/**
 * function that updates the board
 */
void GameLogic::updateboard(){
    bool askAgain = false;
    if(get_turn()== 'X'){
        cout<<"HUMAN'S TURN\n";
        cout<<"Please enter row and column position seperated by a space according to the grid (For example 1 1 is the first row, first column): ";
        string pos ="";
        getline(cin, pos);
        set_position(pos);
        
        if(is_valid_row(get_row()) && is_valid_col(get_col())){
            if(board[get_row()-1][get_col()-1]=='_'){
                board[get_row()-1][get_col()-1] = get_turn();
                check_win('X');
                change_turn();
            }
            else{
                cout<<"A move has been made here! Pick a different spot!";
            }
        }
        else{
            cout<"Enter a valid move!";
        }
    }
    else if(get_turn()== 'O'){
        cout<<"COMP'S TURN\n";

        if(attack()){
                check_win('O');
                change_turn();
            }
        else if(defend()){
                //cout<<"In here";
                check_win('O');
                change_turn();
            }
        else{
                move();
                check_win('O');
                change_turn();
            
        }
    }
}

/**
 * function that prints the board
 */
void GameLogic::show_board(){
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(j ==2 ){
                cout<<board[i][j];
            }
            else{
                cout<<board[i][j]<<" | ";
            }
        //cout<<'\n';
        }
        if(i < 2 ){
            
            cout<<'\n'<<"-----------"<<'\n';
        }
        else{
            cout<<'\n';
        }
        
    }
}

/**
 * function that plays the game
 */
    void GameLogic::play(){
        cout<<"Tic Tac Toe"<<'\n';
        show_board();
        char X = 'X';
        char O = 'O';
        while(true){
            cout<<"Who should play first? (X for you, O for computer): ";
            cin>>turn ;
            if(turn == 'X'){
                break;
            }
            else if(turn =='O'){
                break;
            }

            if(cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Enter something valid";
            }
             
        }
        firstMove = turn;
        cin.ignore();
        while (!gameOver){
            updateboard();///
            cout<<'\n';
            show_board();
            firstMove = ' ';
        }
    }

