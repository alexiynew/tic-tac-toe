#include <iostream>
#include "Painter.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Board.hpp"
#include <string>

const int window_size = 100;
Painter p;
Board b(window_size);
char winer, plr_toe = 'x', comp_toe = 'o';
int plr_win = 0, comp_win = 0, nobody = 0;
enum GameState{Begin, Playing, Stop};
GameState state {Begin};

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	b.draw(p);

	if(state == Begin){
        p.startScreen(window_size);
	}

    if(state == Stop){
        p.endScreen(window_size, plr_win, comp_win, nobody);
    }

	glutSwapBuffers();

}

char makeMove(int x, int y){
    char w = 0;
    b.set(plr_toe, x, y);

    if(b.isWin(plr_toe)){
        return plr_toe;
    }

    b.compMove(comp_toe);

    if(b.isWin(comp_toe)) {
        return comp_toe;
    }

    if(b.isFull()){
        w = '_';
    }

    return w;
}


void click(int button, int status, int x, int y){
	if(button == GLUT_LEFT_BUTTON && status == GLUT_UP){
        switch(state){
        case Begin:
            //16,40,85,60
            if(x > 16 && x < 85 && y > 40 && y < 60){
                b.clear();
                state = Playing;
            }
            break;
        case Playing:
            winer = makeMove(x, y);
            if (winer != 0){
                state = Stop;
                if(winer == '_')
                    nobody++;
                else if (winer == plr_toe)
                    plr_win++;
                else
                    comp_win++;
            }
            break;
        case Stop:
            //17,70,84,90
            if(x > 17 && x < 84 && y > 70 && y < 90){
                b.clear();
                state = Playing;
            }
            break;
        }

	}

	display();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(window_size,window_size);
	glutInitWindowPosition(window_size,window_size);
	glutCreateWindow("Tic-Tac-Toe");

	glEnable( GL_LINE_SMOOTH );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,window_size,window_size,0,-1,1);

	glutDisplayFunc(display);
	glutMouseFunc(click);

	glutMainLoop();

	return 0;
}
