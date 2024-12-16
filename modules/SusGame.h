#pragma once
#include "BoardGame_Classes.h"


template <typename T>
class Sus_Player : public Player<T> {
public:
	int moves = 0;
	Sus_Player(string name, T symbol) : Player<T>(name, symbol) {};
	Sus_Player(T symbol) : Player<T>(symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override {
		if (moves >= 9) return;
		cout << "Row: ";
		cin >> x;
		cout << "Column: ";
		cin >> y;

		while (x < 0 || x > 2 || y < 0 || y > 2) {
			cout << "invalid move\n";
			cout << "Row: ";
			cin >> x;
			cout << "Column: ";
			cin >> y;
		}
	};

};


template <typename T>
class Sus_RandomPlayer : public Sus_Player<T> {
public:
	Sus_RandomPlayer(string name, T symbol) : Sus_Player<T>(name, symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override {
		if (this->moves >= 9) return;
		x = rand() % 3;
		y = rand() % 3;
	};

};

template <typename T>
class Sus_Board : public Board<T> {

	int scores[2];
	bool isover = false;
	Sus_Player<T>** players;
	int n_moves = 0;
	T** board;
public:
	Sus_Board() {
		this->board = new char* [3];
		for (int x = 0; x < 3; x++) {
			this->board[x] = new char[3];
			for (int y = 0; y < 3; y++) {
				this->board[x][y] = '-';
			}
		}
	};

	bool is_win() override {return false;}
	bool is_draw() override { return false; }
	bool game_is_over() override { return isover; }
	bool update_board(int x, int y, T symbol) override {
		if (isover) return true;
		if (this->board[x][y] != '-') {
			return false;
		}

		this->n_moves++;
		this->board[x][y] = symbol;
		players[0]->moves++;
		players[1]->moves++;
		int score = 0;
		score += countmo(x, y, 1, -1, symbol); // diagonal
		score += countmo(x, y, 1, 0, symbol); // hor
		score += countmo(x, y, 1, 1, symbol); // other diagonal
		score += countmo(x, y, 0, 1, symbol); // vert
		if (score) {
			if (this->n_moves % 2 == 1) {
				cout << "Player 1 ";
			}
			else {
				cout << "Player 2 ";
			}

			cout << "scored: " << score << endl;
		}
		//cout << score << endl;

		if (symbol == 'S') {
			scores[0] += score;
		}
		else {
			scores[1] += score;
		}

		if (n_moves == 9) {
			cout << "Player 1: " << scores[0] << endl;
			cout << "Player 2: " << scores[1] << endl;
			if (scores[0] == scores[1]) {
				cout << "Draw!\n";
			}
			else if (scores[0] > scores[1]) {
				cout << "Player 1 Wins!\n";
			}
			else {
				cout << "Player 2 Wins!\n";
			}
			isover = true;
		}
		return true;
	}
	void display_board() override {
		if (isover) return;
		for (int i = 0; i < 3; i++) {
			cout << "\n|";
			for (int j = 0; j < 3; j++) {
				if (this->board[i][j] == '-') {
					cout << "  (" << i << "," << j << ")  |";
				}
				else {
					cout << "    " << this->board[i][j] << "    |";
				}
			}
			cout << "\n-------------------------------";
		}
		cout << endl;
	}


	int count(int x, int y, int dirx, int diry, T symb,int count = 0) {
		if (x > 2 || y > 2 || x < 0 || y < 0)
			return count - 1;
		if (board[x][y] != symb) {
			return count - 1;
		}
		if (count == 2) {
			return symb == 'S' ? count : 0;
		}
		int c = this->count(x + dirx, y + diry, dirx, diry, symb == 'S' ? 'U' : 'S', count + 1);
		if (c == count && symb == 'U') {
			return 0;
		}
		return c;
	}
	bool countmo(int x, int y, int dirx, int diry, T symb) {
		int c0 = count(x, y, dirx, diry, symb);
		int c1 = count(x, y, -dirx, -diry, symb);
		//cout << c0 << " " << c1 << " " << (c0 + c1 + 1) << endl;
		return (c0 + c1 + 1) >= 3;
	};
	void setPlayers(Sus_Player<T>** players) { this->players = players; }
	//friend void setBoard(Sus_Board* b, ToeTacTic_AiPlayer* ai) { ai->setBoard(b->board, 3, 3); };
};

