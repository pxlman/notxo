#pragma once
#include "BoardGame_Classes.h"




template <typename T>
inline int count_moves(T** board,int x, int y, int dirx, int diry, T symb, int count = 0) {
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


template <typename T>
inline bool countmo(T** board, int x, int y, int dirx, int diry, T symb) {
	return count_moves(board, x, y, dirx, diry, symb) + count_moves(board, x, y, -dirx, -diry, symb) + 1 >= 3;
}

template <typename T>
class SubBoard {
	T** board;
	bool isOver;
	char current = '-';
	int moves = 0;
public:
	SubBoard();
	~SubBoard();
	bool makeMove(int x, int y, T symb);
	char getValue() { return current; }
	char getValAt(int x, int y) { return board[x][y]; };
	bool is_game_over() { return isOver; }

};



template <typename T>
class BigBoard : public Board<T>
{
	SubBoard<T>** boards;
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


	T** board;
	int n_moves = 0;
	bool win = false;
	bool draw = false;

public:
	BigBoard();
	~BigBoard();
	bool update_board(int x,int y,T symb) override;
	void display_board() override;
	bool is_win() override { return win; };
	bool is_draw() override { return draw; };
	bool game_is_over() override { return is_win() || is_draw(); }
	vector<vector<T>> getBoard() {
		vector<vector<T>> v(9);
		for (int i = 0; i < 9; i++) {
			v[i] = vector<T>(9);
			for (int j = 0; j < 9; j++) {
				v[i][j] = board[i][j];
			}
		}

		return v;
	}
};

template <typename T>
class Big_Player : public Player<T> {
	T symbol;
public:
	Big_Player(string name, T symbol) : Player<T>(name, symbol) {};
    //Big_Player(char T) : Player<T>(symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;

};


template <typename T>
class Big_RandomPlayer : public Player<T> {
public:
	Big_RandomPlayer(string name, T symbol) : Player<T>(name, symbol) {};
	//void setBoard(ToeTacTic_Board* board) { Player<char>::setBoard/*(board);*/ };
	void getmove(int& x, int& y) override;

};







template <typename T>
BigBoard<T>::BigBoard() {
	boards = new SubBoard<T> * [3];
	board = new char* [3];
	this->rows = 9;
	this->columns = 9;
	for (int i = 0; i < 3; i++) {
		boards[i] = new SubBoard<T>[3];
		board[i] = new char[3] {'-', '-', '-' };
	}
}

template <typename T>
BigBoard<T>::~BigBoard() {
	for (int i = 0; i < 3; i++) {
		delete[] boards[i];
		delete[] board[i];
	}

	delete[] boards;
	delete[] board;
}


template <typename T>
bool BigBoard<T>::update_board(int x, int y, T symb) {
    if(game_is_over()) return false;
	int boardx = x / 3;
	int boardy = y / 3;
	int subx = x % 3;
	int suby = y % 3;

	if (boards[boardx][boardy].is_game_over()) {
		cout << "Board is Already Over" << endl;
		return false;
	}
	auto move = boards[boardx][boardy].makeMove(subx, suby, symb);

	if (!move) {
		cout << "Invalid Move" << endl;
		return false;
	}

	board[boardx][boardy] = boards[boardx][boardy].getValue();
	win = false;
	win = win || countmo(board, boardx, boardy, 1, -1, symb);
	win = win || countmo(board, boardx, boardy, 1, 0, symb);
	win = win || countmo(board, boardx, boardy, 1, 1, symb);
	win = win || countmo(board, boardx, boardy, 0, 1, symb);

	if (win) {
		return true;
	}

	this->draw = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!boards[i][j].is_game_over()) {
				draw = false;
				break;
			}
		}
		if (!draw)
			break;
	}


	return true;
}



template <typename T>
void BigBoard<T>::display_board() {
	cout << endl;

	cout << "  012   345   678" << endl;
	for (int x = 0; x < 9; x++) {
		cout << x << " ";
		for (int y = 0; y < 9; y++) {
			int boardx = x / 3;
			int boardy = y / 3;
			int subx = x % 3;
			int suby = y % 3;
			if (boards[boardx][boardy].is_game_over()) {
				char symbol = tolower(boards[boardx][boardy].getValue());
				int value;
				if (symbol == 'x') {
					value = 0;
				}
				else if (symbol == 'o') {
					value = 1;
				}
				else {
					value = 2;
				}
				cout << symbols[value][subx][suby];
			}
			else {
				cout << boards[boardx][boardy].getValAt(subx, suby);
			}
			if ((y + 1) % 3 == 0 && y != 8) {
				cout << " | ";
			}
		}
		cout << endl;
		if ((x + 1) % 3 == 0 && x != 8) {
			cout << "------*-----*------" << endl;
		}
	}


}




template <typename T>
SubBoard<T>::SubBoard() {
	isOver = false;
	board = new char* [3];
	for (int i = 0; i < 3; i++) {
		board[i] = new char[3] {'-', '-', '-'};
	}
}


template <typename T>
SubBoard<T>::~SubBoard() {
	for (int i = 0; i < 3; i++) {
		delete[] board[i];
	}

	delete[] board;
}


template <typename T>
bool SubBoard<T>::makeMove(int x, int y, T symb) {
	if (board[x][y] != '-') {
		return false;
	}

	if (is_game_over()) {
		return false;
	}

	moves++;
	board[x][y] = symb;


	bool win = false;

	win = win || countmo(board, x, y, 1, -1, symb);
	win = win || countmo(board, x, y, 1, 0, symb);
	win = win || countmo(board, x, y, 1, 1, symb);
	win = win || countmo(board, x, y, 0, 1, symb);

	if (win) {
		isOver = true;
		current = symb;
		return true;
	}

	if (moves == 9) {
		isOver = true;
	}

	return true;

}



template <typename T>
void Big_Player<T>::getmove(int& x, int& y) {
	cout << "Row: ";
	cin >> x;
	cout << "Column: ";
	cin >> y;

	while (x < 0 || x > 8 || y < 0 || y > 8) {
		cout << "invalid move\n";
		cout << "Row: ";
		cin >> x;
		cout << "Column: ";
		cin >> y;
	}
}


template <typename T>
void Big_RandomPlayer<T>::getmove(int& x, int& y) {
	x = rand() % 9;
	y = rand() % 9;
}
