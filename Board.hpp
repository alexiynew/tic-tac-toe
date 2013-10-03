#ifndef BOARD_HPP
#define BOARD_HPP

#pragma once
#include "Painter.hpp"
#include <string>

class Board{
public:
	Board(int);
    static bool checkWin(std::string board, char t);
	void draw(Painter& p);
	bool set(char t, int x, int y);
	bool set(char t, int i);
	bool isFull();
	bool isWin(char);
	void clear();
	char getCurrent(){return current;};
	int fillCount();
	std::string toString();
	bool compMove(char t);
private:
	char map[9]{};
	char current = 'x';
	int width;
	int psize;
	const short triplets[24]{
		0,1,2,3,4,5,6,7,8,
		0,3,6,1,4,7,2,5,8,
		0,4,8,6,4,2
	};
};

#endif // BOARD_HPP
