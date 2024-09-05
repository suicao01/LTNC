#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
using namespace std;

void Title::render(){
    SDL_Surface*image=NULL;
    switch (m) {
case 1:
    item=Title_item::blue;
    image=IMG_Load("assets/gemBlue.png");
    break;
case 2:
    item=Title_item::green;
    image=IMG_Load("assets/gemGreen.png");
    break;
case 3:
    item=Title_item::orange;
    image=IMG_Load("assets/gemOrange.png");
    break;
case 4:
    item=Title_item::red;
    image=IMG_Load("assets/gemRed.png");
    break;
case 5:
    item=Title_item::yellow;
    image=IMG_Load("assets/gemYellow.png");
    break;

case 6:
    item=Title_item::purple;
    image=IMG_Load("assets/gemPurple.png");
    break;
case 7:
    item=Title_item::white;
    image=IMG_Load("assets/gemWhite.png");
    break;
default:
    break;
    }

    texture=SDL_CreateTextureFromSurface(renderer,image);
    SDL_RenderCopy(renderer,texture,NULL,&Tilte_rect);
    SDL_RenderPresent(renderer);
    }

void Title::render_emty(){
SDL_Surface*image=NULL;
switch (status) {
case Title_emty::Dark:
    image=IMG_Load("assets/dark.png");
    break;
case Title_emty::Light:
    image=IMG_Load("assets/light.png");
    break;
}
 if (image == NULL)
    {
        cerr << "Unable to load image! SDL Error: " << SDL_GetError();
    }
    else
    {
 SDL_Texture*texture=SDL_CreateTextureFromSurface(renderer,image);
    SDL_RenderCopy(renderer,texture,NULL,&Tilte_rect);
}
}
void Title::render_selected(){
    SDL_Surface*image=NULL;
    image=IMG_Load("assets/selector.png");
   SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,image);
    SDL_RenderCopy(renderer,texture,NULL,&Tilte_rect);
    SDL_RenderPresent(renderer);

    }

void Title::swapTitle (Title otherTile,SDL_Texture*MoveText,int speed) {
 SDL_Rect thisRect = Tilte_rect;
    SDL_Rect otherRect = otherTile.Tilte_rect;
    for (; otherRect.y != Tilte_rect.y ;) {
        if (MoveText != NULL) {
            otherRect.y += speed;

            if (otherRect.y > Tilte_rect.y) otherRect.y = Tilte_rect.y;
        }
        else if (otherTile.Tilte_rect.y > Tilte_rect.y) {
            otherRect.y -= 1; thisRect.y += 1;
        }
        else {
            otherRect.y += 1; thisRect.y -= 1;
        }
        if (MoveText == NULL) {
            SDL_RenderCopy(renderer, texture, NULL, &thisRect);
            SDL_RenderCopy(renderer, otherTile.texture, NULL, &otherRect);
        }
        else {
            SDL_RenderCopy(renderer, MoveText, NULL, &otherRect);
        }
        SDL_RenderPresent(renderer);
        otherTile.render_emty();
        render_emty();
    }
    for (; otherRect.x != Tilte_rect.x;) {

        if (otherTile.Tilte_rect.x > Tilte_rect.x) {
            otherRect.x -= 1; thisRect.x += 1;
        }
        else {
            otherRect.x += 1; thisRect.x -= 1;
        }
        SDL_RenderCopy(renderer, texture, NULL, &thisRect);
        SDL_RenderCopy(renderer,otherTile.texture, NULL, &otherRect);
        SDL_RenderPresent(renderer);
        otherTile.render_emty();
        render_emty();
    }
}
