#include "Text.h"
#include <sstream>
#include "SDL_utils.h"
#include <vector>
#include "SDL_imagefunction.h"
#include "Board.h"
#include "Game.h"
#include "Sound.h"

using namespace std;


SDL_Rect back_rect{0,0,800,600};
SDL_Rect startbutton={325,440,160,50};
SDL_Rect logo={180,0,500,300};
SDL_Rect resultRect={250,130,300,100};
SDL_Rect newgameSelect={325,440,160,30};
SDL_Rect soundOn={15,400,55,50};
SDL_Rect ScoreBoard={15,200,140,43};
SDL_Rect TargetBoard={15,100,140,43};
SDL_Rect Moves={15,350,30,25};

char *Intostr(long point) {
char*score=new char[7];
stringstream ss;
ss<<point;
string str=ss.str();
int n=str.length();
for (int i=0;i<6;i++) {
    if (i<6-n){score[i]='0';}
    else score[i]=str[i+n-6];
}
score[6]='\0';

return score;
}

char*moveStr (int moves) {
char*score=new char[6];
stringstream ss;
ss<<moves;
string s=ss.str();
int n=s.length();
for (int i=0;i<2;i++) {
    if (i<2-n) score[i]='0';
    else score[i]=s[i+n-2];
}
score[2]='\0';
return score;
}




void Button::create_text (const char*up,const char*down){
    SDL_Surface*image=NULL;
    image=IMG_Load(up);
    up_t=SDL_CreateTextureFromSurface(renderer,image);
    image=IMG_Load(down);
    down_t=SDL_CreateTextureFromSurface(renderer,image);

    }

void Button::render(){

    if (status==Button_status::up)SDL_RenderCopy(renderer,up_t,NULL,&Button_Rect);
    else SDL_RenderCopy(renderer,down_t,NULL,&Button_Rect);
    }

void Game::initialize(){
     if (!LoadMusic()) cerr<<"Fail to load music"<<endl;
    Mix_VolumeChunk(eatable_sound,32);
    Mix_VolumeChunk(selected_sound,64);
    Mix_VolumeChunk(reverse_sound,32);

    Mix_VolumeMusic(128);
        Show_image(renderer,"assets/startBackground.png",back_rect );
         Show_image(renderer,"assets/startbutton.png",startbutton);
         Mix_PlayMusic(background_music,-1);
game_button[3].Button_Rect={15,500,55,50};
game_button[3].renderer=renderer;
for (int i=0;i<3;i++) {
    game_button[i].Button_Rect={300,300+i*70,200,50};
    game_button[i].renderer=renderer;
}
game_button[0].create_text("assets/easybutton.png","assets/easydown.png");
game_button[1].create_text("assets/normalbutton.png","assets/normaldown.png");
game_button[2].create_text("assets/hardbutton.png","assets/harddown.png");
game_button[3].create_text("assets/soundOn.png","assets/mute.png");
bool quit=false;
while (!quit) {
    if (SDL_PollEvent(&e)==0) continue;
    if (e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT) {
   bool play=e.button.x<=450 && e.button.x>=350&& e.button.y<=480 && e.button.y>400;
   if (play) {
    if (!Mix_Paused(-1)) Mix_PlayChannel(-1,reverse_sound,0);
    Show_image(renderer,"assets/startclick.png",startbutton);
    SDL_Delay(50);
    quit=true;
   }

    }
}
}






void Game::Level(){
    bool quit=false;
    Show_image(renderer,"assets/menu.png",back_rect);

    for (int i=0;i<5;i++) {
        game_button[i].render();
    }
   Show_image(renderer,"assets/logo.png",logo);
    SDL_RenderPresent(renderer);

    while (!quit) {
        if (SDL_PollEvent(&e)==0) continue;
        switch (e.type) {
    case SDL_QUIT:
        quit=false;
        break;
    case SDL_MOUSEMOTION:

        for (int i=0;i<5;i++) {
                if(e.button.x<=game_button[i].Button_Rect.x+game_button[i].Button_Rect.w
                   && e.button.x>=game_button[i].Button_Rect.x &&e.button.y<=game_button[i].Button_Rect.y+game_button[i].Button_Rect.h
                   &&e.button.y>=game_button[i].Button_Rect.y){
        game_button[i].status=Button_status::down;


        }
            else {game_button[i].status=Button_status::up;}
            game_button[i].render();
            SDL_RenderPresent(renderer);
        }
        break;
    case SDL_MOUSEBUTTONDOWN :
        if (e.button.button==SDL_BUTTON_LEFT) {
if (!Mix_Paused(-1)) Mix_PlayChannel(-1,reverse_sound,0);
            for (int i=0;i<4;i++) {

              if(e.button.x<=game_button[i].Button_Rect.x+game_button[i].Button_Rect.w
                   && e.button.x>=game_button[i].Button_Rect.x &&e.button.y<=game_button[i].Button_Rect.y+game_button[i].Button_Rect.h
                   &&e.button.y>=game_button[i].Button_Rect.y) {
                    if (game_button[i].status==Button_status::up) game_button[i].status=Button_status::down;
                    else game_button[i].status=Button_status::up;
                    game_button[i].render();
                    SDL_RenderPresent(renderer);
                    SDL_Delay(50);
                    switch (i) {
                case 0:
                    move1=15;
                    target=4000;
                    quit=true;
                    break;
                case 1:
                    move1=15;
                    target=8000;
                    quit=true;
                    break;
                case 2:
                    move1=15;
                    target=15000;
                    quit=true;
                    break;}
                if (i==3) {
                    if (game_button[i].status==Button_status::up) {
                        Mix_ResumeMusic();
                        Mix_Resume(-1);
                    }
                    else{

                    Mix_PauseMusic();
                    Mix_Pause(-1);

                    }
                }

           else game_button[i].status=Button_status::up;
            //SDL_Delay(50);
            break;


            }

        }
    }
    }}
};
int Game::gameplay(){
        Board game_b(renderer);
        long p=0;
        int moveHid=move1;
    Show_image(renderer,"assets/Background.png",back_rect);

    SDL_RenderFillRect(renderer,&Moves);
LoadFont("000000",renderer,ScoreBoard);
LoadFont("Target",renderer,{15,50,70,30});
SDL_SetRenderDrawColor(renderer,0,0,0,255);
SDL_RenderFillRect(renderer,&TargetBoard);
LoadFont("Moves",renderer,{15,300,70,30});
SDL_SetRenderDrawColor(renderer,0,0,0,255);
LoadFont("Score",renderer,{15,160,70,30});
LoadFont(moveStr(moveHid),renderer,Moves);
LoadFont(Intostr(target),renderer,TargetBoard);
 SDL_RenderFillRect(renderer,&ScoreBoard);
 LoadFont(Intostr(p),renderer,ScoreBoard);
    game_b.fill_board();
    bool quit=false;

    while(!quit) {
        if (SDL_PollEvent(&e)==0) continue;
        if (e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT) {
           if (!game_b.Can_swap()) {
               SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderFillRect(renderer,&ScoreBoard);
                SDL_Delay(300);
                SDL_RenderFillRect(renderer,&ScoreBoard);
         game_b.render_board();
                game_b.mix();


           }
           else

 game_b.find_titleselected(e.button.x,e.button.y,moveHid);
            while (game_b.find_match(p)){

                SDL_RenderFillRect(renderer,&Moves);
LoadFont(moveStr(moveHid),renderer,Moves);

                        game_b.dropnewTile(p);


SDL_RenderFillRect(renderer,&ScoreBoard);
LoadFont(Intostr(p),renderer,ScoreBoard);
           }
           if (p>=target) {
            return result(true);
           }

else if(moveHid==0){
            return result(false);
}
        }
    }

return gameplay();
    }

int Game::result (bool res){
    bool quit=false;
    game_button[0].create_text("assets/replaybutton.png","assets/replaydown.png");
    game_button[1].create_text("assets/exitbutton.png","assets/exitdown.png");
    Show_image(renderer,"assets/menu.png",back_rect);

    for (int i=0;i<2;i++) {
        game_button[i].render();
    }
    game_button[3].render();
    if (res) {
        Show_image(renderer,"assets/win.png",resultRect);
    }
    else {Show_image(renderer,"assets/lose.png",resultRect);
    Mix_PlayMusic(gameover_sound,1);}
SDL_RenderPresent(renderer);

    while (!quit) {
        if (SDL_PollEvent(&e) == 0) continue;
        switch (e.type) {
    case SDL_QUIT:
        quit=false;
        break;
    case SDL_MOUSEMOTION:
        for (int i=0;i<2;i++) {
            if (e.button.x <= game_button[i].Button_Rect.x + game_button[i].Button_Rect.w
                    && e.button.x >= game_button[i].Button_Rect.x
                    && e.button.y <= game_button[i].Button_Rect.y + game_button[i].Button_Rect.h
                    && e.button.y >= game_button[i].Button_Rect.y) {
                    game_button[i].status=Button_status::down;

                    }
                    else game_button[i].status=Button_status::up;
                    game_button[i].render();
                    SDL_RenderPresent(renderer);
        }
        break;

       case SDL_MOUSEBUTTONDOWN:
if (!Mix_Paused(-1)) Mix_PlayChannel(-1,selected_sound,0);
            for (int i = 0; i < 2; i++) {

                if (e.button.x <= game_button[i].Button_Rect.x + game_button[i].Button_Rect.w
                    && e.button.x >= game_button[i].Button_Rect.x
                    && e.button.y <= game_button[i].Button_Rect.y + game_button[i].Button_Rect.h
                    && e.button.y >= game_button[i].Button_Rect.y) {

                if (game_button[i].status ==Button_status::up) game_button[i].status = Button_status::down;
                    else game_button[i].status = Button_status::up;
                    game_button[i].render();
                    SDL_RenderPresent(renderer);
                    SDL_Delay(50);
                    switch(i) {
                case 0:
initialize();
Level();
                   gameplay();

                    break;
                case 1:
                    SDL_Quit();

                    break;

                    }
if (i==2) {
                        game_button[i].status = Button_status::up;
                        if (i == 1) return -1;
                        else return i;

                }
            }
        }
        break;
    }
    }
    return result(res);
    }
