#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>



enum class Title_item {
emty,yellow,
blue,white,purple,
orange,
red,
green,
select
};

enum class Title_emty{
Dark,Light
};
class Title {
int x=0,y=0;
int w=65,h=65;
public:
    SDL_Renderer*renderer=NULL;
    SDL_Texture*texture=NULL;
    int m=0;
    SDL_Rect Tilte_rect={x,y,w,h};
    Title_item item=Title_item::emty;
    Title_emty status=Title_emty::Dark;
    Title() {};
    ~Title(){};
    void render();
    void render_emty();
    void render_selected();
    void swapTitle (Title otherTile,SDL_Texture*MoveText=NULL,int speed=30);
};
#endif // TILE_H
