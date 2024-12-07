//
// Created by pxlman on 12/5/24.
//

#ifndef XOGAME_WORDIC_H
#define XOGAME_WORDIC_H
#include "BoardGame_Classes.h"
#include <iomanip>
#include <cctype>
#include <fstream>
#include <vector>

vector<string> getWords(){
    ifstream file("modules/dic.txt");
    vector<string> words = {};
    string word = "";
    while(file >> word){
        words.push_back(word);
    }
    file.close();
    return words;
}
vector<string> words = getWords();

template <typename T>
class Wordic_Player : public Player<T> {
public:
    Wordic_Player (string name, T symbol): Player<T>(name,symbol){}
    void getmove(int& x, int& y){
        cout << "\nPlease enter your move x, y (0 to 2) and letter separated by spaces: ";
        cin >> x >> y;
        cin >> this->symbol;
    }
};

template <typename T>
class Wordic_Random_Player : public RandomPlayer<T>{
public:
    Wordic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int& x, int& y) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        this->symbol = 'A' + rand() % ('Z' - 'A');
    }
};

template<typename T>
class Wordic_Board: public Board<T>{
private:
    bool validMove(int &x,int &y, T &symbol){
        if ((y >= 0 && y <= 2) && (x >= 0 && x <= 2) && isalpha(symbol)) return true;
        return false;
    }
public:
    Wordic_Board(){
        this->rows = 3;
        this->columns = 3;
        this->board = new char*[this->rows];
        for (int y = 0; y < this->rows; ++y) {
            this->board[y] = new char[this->columns];
            for (int x = 0; x < this->columns; ++x) {
                this->board[y][x] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board(int x, int y, T symbol){
        // Only update if move is valid
        if ( validMove(x,y, symbol) && (this->board[y][x] == 0)) {
            if (symbol == 0){
                this->n_moves--;
                this->board[y][x] = 0;
            }
            else {
                this->n_moves++;
                this->board[y][x] = toupper(symbol);
            }
            return true;
        }
        else return false;
    }
    void display_board(){
        for (int y = 0; y < this->rows; y++) {
            cout << "\n";
            for (int x = 0; x < this->columns; x++) {
                cout << " (" << x << "," << y << ")";
                cout << setw(2) << this->board[y][x] << " |";
            }
        }
        cout << "\n\\---------------------------------------------/";
        cout << endl;
    }
    bool is_win(){
        for (auto it = words.begin(); it != words.end() ; ++it) {
            // Check rows
            string t;
            t = string(1,this->board[0][0]) + this->board[0][1] + this->board[0][2];
            if(t == *it) return true;
            t = string(1,this->board[1][0]) + this->board[1][1] + this->board[1][2];
            if(t == *it) return true;
            t = string(1,this->board[2][0]) + this->board[2][1] + this->board[2][2];
            if(t == *it) return true;
            // Check rows
            t = string(1,this->board[0][0]) + this->board[1][0] + this->board[2][0];
            if(t == *it) return true;
            t = string(1,this->board[0][1]) + this->board[1][1] + this->board[2][1];
            if(t == *it) return true;
            t = string(1,this->board[0][2]) + this->board[1][2] + this->board[2][2];
            if(t == *it) return true;
            // Check diagonals
            t = string(1,this->board[0][0]) + this->board[1][1] + this->board[2][2];
            if(t == *it) return true;
            t = string(1,this->board[0][2]) + this->board[1][1] + this->board[2][0];
            if(t == *it) return true;
        }
        return false;
    }
    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }
    bool game_is_over(){
        return is_win() || is_draw();
    }
};





#endif //XOGAME_WORDIC_H
