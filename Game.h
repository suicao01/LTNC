#ifndef GAME_H
#define GAME_H
#include "Board.h"

enum class Button_status{
up,
down
};

class Button {
int x=0,y=0;
int w=0,h=0;

SDL_Texture*up_t=NULL;
SDL_Texture*down_t=NULL;
public:

    SDL_Renderer*renderer=NULL;
    Button_status status=Button_status::up;
    SDL_Rect Button_Rect={x,y,w,h};
    Button(){};
    Button(SDL_Renderer*renderer_,SDL_Rect rect):renderer(renderer_),Button_Rect (rect) {};
    void create_text(const char*up,const char*down);
    void render();
};

class Game{
SDL_Renderer*renderer=NULL;
SDL_Event e;
Board game_b;
long p=0, target=0;
int move1=0;
Button game_button[5];
public:
    Game(SDL_Renderer*renderer_,SDL_Event e_) {
    renderer=renderer_;
    e=e_;
    }
    void initialize();
    void Level();
    int gameplay();
    int result(bool res);

};
//char *IntTostr(long point);
char*moveStr(int moves);
#endif // GAME_H
