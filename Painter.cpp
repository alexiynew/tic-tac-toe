#include "Painter.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <cstring>
#include <stdlib.h>


void Painter::rect(int x1, int y1, int x2, int y2){
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void Painter::setColor(Color c){
	this->current = c;
	static const struct{
		float r,g,b,a;
	} Colors[]{
		{1,1,1,1},
		{0,0,0,1},
		{0,0,1,1},
		{0.1,0.7,0.1,1},
		{0.5,0.5,0.5,1},
		{0,0,0,0.7}
	};

	glColor4f(Colors[static_cast<int>(c)].r,
			  Colors[static_cast<int>(c)].g,
			  Colors[static_cast<int>(c)].b,
              Colors[static_cast<int>(c)].a);
}

void Painter::drawO(int x, int y){
	Color cc = this->current;
	glBegin(GL_POLYGON);
	for(float a=0; a<2*M_PI; a+=0.1){
		glVertex2f(sin(a)*12+x, cos(a)*12+y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	this->setColor(Color::WHITE);
	for(float a=0; a<2*M_PI; a+=0.1){
		glVertex2f(sin(a)*8+x, cos(a)*8+y);
	}
	glEnd();
	this->setColor(cc);
}

void Painter::drawX(int x, int y){
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(x-11,y-11);
	glVertex2f(x+11,y+11);
	glVertex2f(x+11,y-11);
	glVertex2f(x-11,y+11);
	glEnd();
	glLineWidth(1);
}


void Painter::startScreen(int w_size){
    setColor(Color::A_BLACK);
    rect(0,0,w_size,w_size);

    setColor(Color::GREY);
    rect(16,40,85,60);

    glColor3f(0.95,0.95,0.95);
    print("New Game", 20, 54);

}

void Painter::endScreen(int w_size, int pw, int cw, int nw){
    setColor(Color::A_BLACK);
    rect(0,0,w_size,w_size);

    setColor(Color::WHITE);
    print("Win: ", 20, 20);
    print("Lose:", 20, 35);
    print("Tie: ", 20, 50);

    print(std::to_string(pw), 60, 20);
    print(std::to_string(cw), 60, 35);
    print(std::to_string(nw), 60, 50);

    setColor(Color::GREY);
    rect(17,70,84,90);
    glColor3f(0.95,0.95,0.95);
    print("Repeat?", 28, 84);

}

void Painter::print(std::string text, int x, int y){
    glRasterPos2f(x, y);
    unsigned char s[text.size()];
    strncpy((char*)s, text.c_str(), sizeof(s));
    s[text.size()] = 0;
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, s);
}
