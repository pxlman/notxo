#pragma once
#include "BoardGame_Classes.h"

class Sus_Player : public Player<char> {
public:
	int moves = 0;
	Sus_Player(string name, char symbol) : Player<char>(name, symbol) {};
	Sus_Player(char symbol) : Player<char>(symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;

};

class Sus_RandomPlayer : public Sus_Player {
public:
	Sus_RandomPlayer(string name, char symbol) : Sus_Player(name, symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;

};


class Sus_Board : public Board<char> {

	int scores[2];
	bool isover = false;
	Sus_Player** players;
public:
	Sus_Board();
	bool is_win() override;
	bool is_draw() override { return false; };
	bool game_is_over() override { return isover; }
	bool update_board(int x, int y, char symbol) override;
	void display_board() override;
	int count(int x, int y, int dirx, int diry, char symb, int count = 0);
	bool countmo(int x, int y, int dirx, int diry, char symb);
	void setPlayers(Sus_Player** players) { this->players = players; }

	vector<vector<char>> getAsVector() {
		vector<vector<char>> v(3);
		for (int i = 0; i < 3; i++) {
			v[i] = vector<char>(3);
			for (int j = 0; j < 3; j++) {
				v[i][j] = board[i][j];
			}
		}

		return v;

	}
	//friend void setBoard(Sus_Board* b, ToeTacTic_AiPlayer* ai) { ai->setBoard(b->board, 3, 3); };
};
