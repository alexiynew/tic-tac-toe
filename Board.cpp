#include "Board.hpp"
#include <iostream>

Board::Board(int w): width{w}, psize{(w-4)/3}{clear();};



void Board::draw(Painter& p){
	p.setColor(Painter::Color::WHITE);
	p.rect(0,0,width,width);
	p.setColor(Painter::Color::BLACK);
	p.rect(5,5,width-5,width-5);
	for(int y=0;y<3;++y)
		for(int x=0;x<3;++x){
			int x1 = psize*x+2*x;
			int x2 = x1+psize;
			int y1 = psize*y+2*y;
			int y2 = y1+psize;
			p.setColor(Painter::Color::WHITE);
			p.rect(x1,y1,x2,y2);
			switch(map[y*3+x]){
				case 'o':
					p.setColor(Painter::Color::BLUE);
					p.drawO(x1+psize/2, y1+psize/2);
					break;
				case 'x':
					p.setColor(Painter::Color::GREEN);
					p.drawX(x1+psize/2, y1+psize/2);
					break;
				default:
					break;
			}

		}
}

bool Board::set(char t, int x, int y){

	int bx = x / psize;
	int by = y / psize;
	if(bx >= 0 && bx < 3 && by >= 0 && by < 3 && map[by*3+bx]=='_'){
        current = t;
		map[by*3+bx] = current;
		return true;
	}
	return false;
}

bool Board::set(char t, int i){

	if(i >= 0 && i < 9 && map[i]=='_'){
        current = t;
		map[i] = current;
		return true;
	}
	return false;
}

bool Board::isFull(){
	for(int i=0; i<9; i++)
		if(map[i] == '_')
			return false;
	return true;
}


bool Board::isWin(char t){
    for(int i=0; i<24; i+=3){
		if(map[triplets[i]] == t && map[triplets[i+1]] == t && map[triplets[i+2]] == t)
			return true;
	}
	return false;
}
void Board::clear(){
	for(int i=0; i<9; i++)
		map[i] = '_';
}

int Board::fillCount(){
    int count = 0;
    for(int i=0; i<9; i++)
        if(map[i] != '_') count++;
    return count;
}
std::string Board::toString(){
    std::string code = "";
    for(int i=0; i<9; i++){
        code += (map[i]);
    }
    return code;
}


bool Board::compMove(char t){

    int best = -1;
    float bestK = 0;
    for(int i=0; i<9; i++){
        float k = 0;
        if(map[i] == '_'){

            for(int j=0; j<24; j+=3){
                if(triplets[j] == i || triplets[j+1] == i || triplets[j+2] == i){
                    int oc = 0, xc = 0, nc = 0;

                    for(int ii=0; ii<3;ii++){
                        switch(map[triplets[j+ii]]){
                            case '_' : nc++; break;
                            case 'x' : xc++; break;
                            case 'o' : oc++; break;
                        }
                    }
                    if(oc == 2 || xc ==2)
                        return set(t, i);

                    k += oc*( t=='o' ? 4 : 2) + xc*( t=='x' ? 4 : 2) + nc;
                }
            }

            if(k > bestK){
                best = i;
                bestK = k;
            }
        }
    }
    return set(t, best);
}


