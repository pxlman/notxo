//
// Created by pxlman on 12/5/24.
//

#ifndef XOGAME_PYRAMIC_H
#define XOGAME_PYRAMIC_H
#include "BoardGame_Classes.h"
#include <iomanip>
#include <cctype>

template<typename T>
class PyramicBoard: public Board<T>{
private:
    bool validMove(int &x,int &y){
        if (y == 0 && x == 2) return true;
        if (y == 1 && (x <= 3 && x >= 1)) return true;
        if (y == 2 && (x <= 4 && x >= 0)) return true;
        return false;
    }
public:
    PyramicBoard(){
        this->rows = 3;
        this->columns = 5;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board(int x, int y, T symbol){
        // Only update if move is valid
        if ( validMove(x,y) && (this->board[x][y] == 0|| symbol == 0)) {
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
        return false;
    }
    void display_board(){
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < 2-i; ++j) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << ' ' << " |";
            }
            for (int j = 2 - i; j < 2 + i; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            for (int j = 2 + i; j < this->columns; ++j) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << ' ' << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }
    bool is_win(){
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
                (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
            return true;
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



#endif //XOGAME_PYRAMIC_H
