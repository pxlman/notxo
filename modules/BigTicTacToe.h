#pragma once
#include "BoardGame_Classes.h"




inline int count_moves(char** board,int x, int y, int dirx, int diry, char symb, int count = 0) {
	if (x > 2 || y > 2 || x < 0 || y < 0)
		return count - 1;
	if (board[x][y] != symb) {
		return count - 1;
	}
	if (count == 2) {
		return count;
	}
	return count_moves(board,x + dirx, y + diry, dirx, diry, symb, count + 1);
}


inline bool countmo(char** board, int x, int y, int dirx, int diry, char symb) {
	return count_moves(board, x, y, dirx, diry, symb) + count_moves(board, x, y, -dirx, -diry, symb) + 1 >= 3;
}

class SubBoard {
	char** board;
	bool isOver;
	char current = '-';
	int moves = 0;
public:
	SubBoard();
	~SubBoard();
	bool makeMove(int x, int y, char symb);
	char getValue() { return current; }
	char getValAt(int x, int y) { return board[x][y]; };
	bool is_game_over() { return isOver; }

};



class BigBoard : public Board<char>
{
	SubBoard** boards;
	const string symbols[3][3] = {
		{"\\ /",
		 " X ",
		 "/ \\"},//x
		{" - ",
		 "| |",
		 " - "},//o
		{"   ",
		 " - ",
		 "   "}//-
	};

	bool win = false;
	bool draw = false;

public:
	BigBoard();
	~BigBoard();
	bool update_board(int x,int y,char symb) override;
	void display_board() override;
	bool is_win() override { return win; };
	bool is_draw() override { return draw; };
	bool game_is_over() override { return is_win() || is_draw(); }
	
	// returns a 9x9 vector of all the boards
	vector<vector<char>> getWholeBoard() {
		vector<vector<char>> v(9);

		for (int i = 0; i < 9; i++) {
			v[i] = vector<char>(9);
			for (int j = 0; j < 9; j++) {
                int boardx = x / 3;
                int boardy = y / 3;
                int subx = x % 3;
                int suby = y % 3;

				v[i][j] = boards[boardx][boardy].getValAt(subx, suby);
			}
		}
		return v;
	}

	// returns a 3x3 board of the final results of the big board
	vector<vector<char>> getBigBoard() {
		vector<vector<char>> v(3);
		for (int i = 0; i < 3; i++) {
			v[i] = vector<char>(3);
			for (int j = 0; j < 3; j++) {
				v[i][j] = boards[i][j].getValue();
			}
		}
		return v;
	}
};

class Big_Player : public Player<char> {
public:
	Big_Player(string name, char symbol) : Player<char>(name, symbol) {};
	Big_Player(char symbol) : Player<char>(symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;
};


class Big_RandomPlayer : public Player<char> {
public:
	Big_RandomPlayer(string name, char symbol) : Player<char>(name, symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;

};

