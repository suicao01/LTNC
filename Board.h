#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "Sound.h"
#include "Tile.h"


using namespace std;

const int rows= 8;
const int columns= 8;
const int numOfitem=7;

class Board {
SDL_Renderer*renderer=NULL;
long  hpoint=0;
int speed=30;
public:


    Title title_board[rows][columns];
    Board(){};
    Board(SDL_Renderer*renderer_):renderer(renderer_) {};
    void render_board();
    void find_titleselected(int xmouse,int ymouse,int &move);
    void fill_board();
    bool find_match(long &cpoint);

    void dropnewTile(long &point);
    void mix ();
    bool Can_swap();



};

#endif // BOARD_H
