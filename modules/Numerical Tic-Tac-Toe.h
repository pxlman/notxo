#ifndef UNTITLED2_NUMERICAL_TIC_TAC_TOE_H
#define UNTITLED2_NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <unordered_set>
#include <vector>
#include <numeric>

template <typename T>
class Numerical_Board : public Board<T> {
public:
    bool isEven;
    Numerical_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    std::unordered_set<int> used_numbers; // Track used numbers
};

template <typename T>
class Numerical_Player : public Player<T> {
public:
    Numerical_Player(std::string name, T symbol);
    void getmove(int& x, int& y);
    bool isEven;
};

template <typename T>
class Numerical_Random_Player : public Numerical_Player<T> {
public:
    Numerical_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Constructor for Numerical_Board
template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
    this->board = new T * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]{ 0 }; // Initialize to 0
    }
    this->n_moves = 0;
}

// Update the board with the player's number
template <typename T>
bool Numerical_Board<T>::update_board(int x, int y, T number) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || this->board[x][y] != 0 || used_numbers.count(number)) {
        return false;
    }
    this->board[x][y] = number;
    used_numbers.insert(number);
    this->n_moves++;
    return true;
}

// Display the board
template <typename T>
void Numerical_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j]==0){
                cout << "  (" << i << "," << j << ")  |";
            }else{
                cout<<"    "<<this->board[i][j]<<"    |";
            }
        }
        cout << "\n-------------------------------";
    }
    cout << endl;
}

// Check for a winning condition
template <typename T>
bool Numerical_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        // Check rows and columns
        if ((((this->board[i][0]+this->board[i][1]+ this->board[i][2])==15)&&(this->board[i][0]!=0 &&this->board[i][1]!=0&&this->board[i][2]!=0))||
            (((this->board[0][i]+ this->board[1][i]+ this->board[2][i])==15)&&(this->board[0][i]!=0&&this->board[1][i]!=0&&this->board[2][i]!=0)))
        {
            return true;
        }
    }
    // Check diagonals
    if ((((this->board[0][0] + this->board[1][1] + this->board[2][2])==15)&&(this->board[0][0]!=0 && this->board[1][1]!=0 &&this->board[2][2]!=0)) ||
            (((this->board[0][2] + this->board[1][1] +  this->board[2][0]==15)&&(this->board[0][2]!=0&& this->board[1][1]!=0 &&  this->board[2][0]!=0)))){
        return true;
    }
    return false;
}

// Check for a draw
template <typename T>
bool Numerical_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Numerical_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(std::string name, T symbol) : Player<T>(name, symbol) {
}

// Get move from the player
template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move row number and column number (0 to 2) Separated by Spaces: ";
    cin>>x>>y;
    cout<<"Enter the number:";
    cin >> this->symbol;
    while ((this->isEven && this->symbol % 2 == 1) ||
     (!this->isEven && this->symbol % 2 == 0) || this->symbol <= 0 || this->symbol > 9) {
        cout << "Invalid!\n\n" << "Enter your move row number and column number (0 to 2) Separated by Spaces: ";
        cin >> x >> y;
        cout<<"Enter the number:";
        cin >> this->symbol;
    }
}
// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : Numerical_Player<T>("computer", symbol) {
    string word;
    cin.ignore();
    getline(cin,word);
    this->name =word;
    srand(static_cast<unsigned int>(time(0)));
}// Seed RNG
// Get random move
template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    do {
        x = rand() % 3;
        y = rand() % 3;
        this->symbol = rand() % 9 + 1;  // Random number 1-9
    } while (this->symbol % 2 == this->isEven);

}
#endif // UNTITLED2_NUMERICAL_TIC_TAC_TOE_H
