#ifndef PAINTER_HPP
#define PAINTER_HPP

#pragma once
#include <string>

class Painter{
public:
	enum class Color{WHITE, BLACK, BLUE, GREEN, GREY, A_BLACK};
	void rect(int, int, int, int);
	void setColor(Color c);
	void drawX(int, int);
	void drawO(int, int);
	void startScreen(int w_size);
	void endScreen(int w_size, int pw, int cw, int nw);
private:
	Color current;
	void print(std::string text, int x, int y);
};

#endif // PAINTER_HPP
