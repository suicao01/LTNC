#include "Sound.h"
#include "SDL_utils.h"
#include"SDL_imagefunction.h"
#include "Tile.h"
#include "Board.h"
#include "Game.h"
#include <ctime>


using namespace std;

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;




int main(int argc, char*args[]) {



   SDL_Window* window;
    SDL_Renderer* renderer;
    srand(time(0));
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "bejeweled");

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        Game GameH(renderer, e);
GameH.initialize();
GameH.Level();

        while (!quit) {
            int temp = GameH.gameplay();
            if (temp == -1) quit = true;
            else if (temp == 1) break;
            else continue;
        }
    }
quitSDL(window,renderer);
    return 0;
}
