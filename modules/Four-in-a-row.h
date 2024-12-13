#ifndef UNTITLED2_FOUR_IN_A_ROW_H
#define UNTITLED2_FOUR_IN_A_ROW_H
#include "BoardGame_Classes.h"
template <typename T>
class Four_in_a_row_Board:public Board<T> {
public:
    Four_in_a_row_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Four_in_a_row_Player : public Player<T> {
public:
    Four_in_a_row_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Four_in_a_row_Random_Player : public RandomPlayer<T>{
public:
    Four_in_a_row_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Four_in_a_row_Board<T>::Four_in_a_row_Board() {
    this->rows = 6 ; this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Four_in_a_row_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (y < 0 || y >= this->columns || this->board[0][y] != T()) return false;
    for (int i = this->rows - 1; i >= 0; --i) {
        if (this->board[i][y] == T()) {
            this->board[i][y] = mark;
            this->n_moves++;
            return true;
        }
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Four_in_a_row_Board<T>::display_board() {
    for(int k=0;k<this->columns;k++){
        cout<<" "<<"("<<k+1<<")";
    }
    for (int i = 0; i < this->rows; i++) {
        cout<<endl << "|";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j]<< " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Four_in_a_row_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Check columns wins
            if (i <= this->rows - 4 &&
                this->board[i][j] != T() &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j] &&
                this->board[i][j] == this->board[i + 3][j]) {
                return true;
            }

            // Check rows wins
            if (j <= this->columns - 4 &&
                this->board[i][j] != T() &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] &&
                this->board[i][j] == this->board[i][j + 3]) {
                return true;
            }
            //check Diagonal top_left to bottom_right
            if (i <= this->rows - 4 && j <= this->columns - 4 &&
                this->board[i][j] != T() &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] &&
                this->board[i][j] == this->board[i + 3][j + 3]) {
                return true;
            }

            // Check Diagonal bottom_left to top_right
            if (i >= 3 && j <= this->columns - 4 &&
                this->board[i][j] != T() &&
                this->board[i][j] == this->board[i - 1][j + 1] &&
                this->board[i][j] == this->board[i - 2][j + 2] &&
                this->board[i][j] == this->board[i - 3][j + 3]) {
                return true;
            }
        }
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Four_in_a_row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Four_in_a_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Four_in_a_row_Player<T>::Four_in_a_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_in_a_row_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter a number from these columns (1 to 7): ";
    cin >> y;
    y=y-1;
}

// Constructor for X_O_Random_Player
template <typename T>
Four_in_a_row_Random_Player<T>::Four_in_a_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    string word;
    cin.ignore();
    getline(cin,word);
    this->name =word; //"Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Four_in_a_row_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;//random 1 to 7
    x = -1; // Row is determined by the board logic, not needed here
}
#endif //UNTITLED2_FOUR_IN_A_ROW_H
