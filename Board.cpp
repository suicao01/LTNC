#include "Sound.h"
#include "SDL_utils.h"
#include "Board.h"

using namespace std;



void Board::render_board(){
    for (int i=0;i<columns;i++) {
        for (int j=0;j<rows;j++) {
            title_board[j][i].render();
        }
    }
    }

void Board::find_titleselected(int xmouse,int ymouse,int &move) {
 if (!Mix_Paused(-1))    Mix_PlayChannel(-1,selected_sound,0);
static int count_select = 0;
   static  int tempR = 0, tempC = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((xmouse <= title_board[i][j].Tilte_rect.x + title_board[i][j].Tilte_rect.w) && (xmouse >= title_board[i][j].Tilte_rect.x)
                && (ymouse <= title_board[i][j].Tilte_rect.y + title_board[i][j].Tilte_rect.h) && (ymouse >= title_board[i][j].Tilte_rect.y))
            {
                if (title_board[i][j].item != Title_item::select && title_board[i][j].item !=Title_item::emty && count_select <= 1) {
                    count_select++;
                    if (count_select == 1) {
                        tempR = i;
                        tempC = j;
                    }
                    title_board[i][j].item = Title_item::select;
                    title_board[i][j].render_selected();
                    if (count_select == 2) {
                        move--;
                        if (((i == tempR - 1 && j == tempC) || (i == tempR + 1 && j == tempC) ||
                            (i == tempR && j == tempC - 1) || ((i == tempR && j == tempC + 1)))) {
                            swap(title_board[i][j].m, title_board[tempR][tempC].m);
                            title_board[i][j].swapTitle(title_board[tempR][tempC]);
                            title_board[i][j].render();
                            title_board[tempR][tempC].render();

                            if (!find_match(hpoint)) {
                                swap(title_board[i][j].m, title_board[tempR][tempC].m);

if (Mix_Paused(-1)) Mix_PlayChannel(1,reverse_sound,0);
                                title_board[tempR][tempC].swapTitle(title_board[i][j]);
                            }

                            title_board[i][j].render();
                            title_board[tempR][tempC].render();
                        }
                        else
                        {
                            title_board[i][j].render();
                            title_board[tempR][tempC].render();
                        }
                        count_select =0;
                    }

                    break;
                }
                else if (title_board[i][j].item == Title_item::select && count_select>2) {

                    title_board[i][j].render();


                }
            }
        }
    }
}


void Board::fill_board(){
    for (int i=0;i<columns;i++) {
        for (int j=0;j<rows;j++) {
if ((i%2==0 && j%2==0) || (i%2==1 && j%2==1)) {
    title_board[i][j].status=Title_emty::Dark;
}
else title_board[i][j].status=Title_emty::Light;

        title_board[j][i].m=rand()%numOfitem+1;
        title_board[j][i].Tilte_rect.x=240+i*65;
        title_board[j][i].Tilte_rect.y=35+j*65;
        if (i>=2 && title_board[j][i-2].m==title_board[j][i-1].m) {
            if (title_board[j][i].m==title_board[j][i-1].m) {
                j--;
continue;
            }
        }
        if (j>=2 && title_board[j-2][i].m==title_board[j-1][i].m) {
            if (title_board[j][i].m==title_board[j-1][i].m) {
                j--;
                continue;
            }
        }
        title_board[j][i].renderer=renderer;
        title_board[j][i].render();
        }
    }
}


bool Board::find_match(long &count_point){

for (int i=0;i<rows;i++) {
        int k=1;
    for (int j=0;j<columns-2;) {
        if (k<columns && title_board[i][j].m==title_board[i][k].m) {
            k++;
            continue;
        }
        if (k-j>=3 ) {
            count_point+=(k-j)*200;
            for (int temp=j;temp<k;temp++) {
                title_board[i][temp].item=Title_item::emty;
                if (!Mix_Paused(-1)) {
                    Mix_Paused(1);
                    Mix_PlayChannel(1,eatable_sound,0);
                }
                title_board[i][temp].render_emty();
            }
            SDL_RenderPresent(renderer);
        }
        int countType=0;
        if (k-j>=5) {

            int temp=title_board[i][j].m;
            for (int i=0;i<columns;i++) {
                for (int j=0;j<rows;j++) {
                    if (title_board[j][i].m==temp) {
                        title_board[j][i].item=Title_item::emty;
                        title_board[j][i].render_emty();
                        countType++;
                    }
                }
            }
            SDL_RenderPresent(renderer);
            count_point+=countType*200;
        }
        j=k;
    }
}
for (int i=0;i<columns;i++) {
        int k=1;
    for (int j=0;j<rows-2;) {
        if (k<rows && title_board[j][i].m==title_board[k][i].m) {
            k++;
            continue;
        }
        if (k-j>=3) {
            count_point+=(k-j)*200;
            for (int temp=j;temp<k;temp++) {
                title_board[temp][i].item=Title_item::emty;
                if (!Mix_Paused(-1)) {
                    Mix_Paused(1);
                    Mix_PlayChannel(1,eatable_sound,0);
                }
                title_board[temp][i].render_emty();
            }
            SDL_RenderPresent(renderer);
        }
        int countType=0;
        if (k-j>=5) {
            int temp=title_board[i][j].m;
            for (int i=0;i<columns;i++) {
                for (int j=0;j<rows;j++) {
                    if (title_board[j][i].m==temp) {
                        title_board[j][i].item=Title_item::emty;
                        title_board[j][i].render_emty();
                        countType++;
                    }
                }
            }
            SDL_RenderPresent(renderer);
            count_point+=countType*200;
        }
        j=k;
    }
}
for (int i=0;i<rows;i++) {
    for (int j=0;j<columns;j++) {
        if (title_board[i][j].item==Title_item::emty){
            return true;
        }
    }
}
return false;


}

void Board::dropnewTile(long &point) {
for (int i=0;i<columns;i++) {
    static int k=0;
    for (int j=rows-1;j>=0;j--) {
        if (title_board[j][i].item==Title_item::emty) {
            for ( k=j-1;k>=0;k--) {
                if (title_board[k][i].item!=Title_item::emty) {
                    title_board[j][i].m=title_board[k][i].m;
                    title_board[k][i].item=Title_item::emty;
                    title_board[k][i].render_emty();
                    for (int t=k;t<j;t++) {
                        title_board[t][i].swapTitle(title_board[t][i],title_board[k][i].texture,speed);
                    }
                    title_board[j][i].render();
                    break;
                }
                else continue;
            }
        }
    }
    for (int j=columns-1;j>=0;j--) {
        if (title_board[j][i].item==Title_item::emty) {
            for (k=j;k>=0;k--) {
                title_board[0][i].m=rand()%numOfitem+1;
                title_board[0][i].render();
                if (k==0) break;
                title_board[k][i].m=title_board[0][i].m;
                title_board[0][i].item=Title_item::emty;
                title_board[0][i].render_emty();
                for (int t=0;t<k;t++) {
                    title_board[t][i].swapTitle(title_board[t][i],title_board[0][i].texture,speed);
                }
                title_board[k][i].render();
            }
        }
    }
}
}

void Board::mix (){
int t_board[rows][columns];
bool check[rows][columns]={0};
for (int i=0;i<rows;i++) {
    for (int j=0;j<columns;j++) {
        t_board[i][j]=title_board[i][j].m;
    }
}
for (int i=0;i<rows;i++) {
    for (int j=0;j<columns;j++) {
        int rn=rand()%rows,rd = rand() % columns;
        if(check[rn][rd]) {
            j--;
            continue;
        }
        else {
            title_board[rn][rd].m=t_board[i][j];
            check[rn][rd]=true;
        }
    }
}
if (!Can_swap()) mix();
}

bool Board::Can_swap(){
    Board temp_board;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<columns;j++) {
            temp_board.title_board[i][j].m=title_board[i][j].m;
        }
    }
    for (int i=0;i<rows;i++) {
        for (int j=0;j<columns-1;j++) {
            swap(temp_board.title_board[i][j].m,temp_board.title_board[i][j+1].m);
            if (temp_board.find_match(hpoint)) {
                return true;
            }
            swap(temp_board.title_board[i][j].m,temp_board.title_board[i][j+1].m);
        }
    }
     for (int i=0;i<columns-1;i++) {
        for (int j=0;j<rows;j++) {
            swap(temp_board.title_board[i][j].m,temp_board.title_board[i+1][j].m);
            if (temp_board.find_match(hpoint)) {
                return true;
            }
            swap(temp_board.title_board[i][j].m,temp_board.title_board[i+1][j].m);
        }
    }
    return false;
    }





