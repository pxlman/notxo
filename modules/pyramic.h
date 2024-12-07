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
        if ( validMove(x,y) && (this->board[y][x] != symbol)) {
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
            for (int x = 0; x < 2-y; x++) {
                cout << "  " << ' ' << " " << ' ' << " ";
                cout << setw(2) << ' ' << "  ";
            }
            for (int x = 2-y; x <= 2+y; x++) {
                cout << " (" << x << "," << y << ")";
                cout << setw(2) << this->board[y][x] << " |";
            }
        }
        cout << "\n\\---------------------------------------------/";
        cout << endl;
    }
    bool is_win(){
        // Check middle col
        if(this->board[0][2] == this->board[1][2] && this->board[2][2] == this->board[1][2] && this->board[1][2] != 0) return true;
        // Check rows
        if(this->board[1][2] == this->board[1][1] && this->board[1][1] == this->board[1][3] && this->board[1][3] != 0) return true;
        if(this->board[2][2] == this->board[2][1] && this->board[2][1] == this->board[2][3] && this->board[2][3] != 0) return true;
        if(this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][2] != 0) return true;
        if(this->board[2][4] == this->board[2][3] && this->board[2][3] == this->board[2][2] && this->board[2][2] != 0) return true;
        // Check diagonals
        if(this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[2][4] != 0) return true;
        if(this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[2][0] != 0) return true;

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
