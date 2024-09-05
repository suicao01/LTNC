#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

extern Mix_Music* background_music;

extern Mix_Chunk* selected_sound;
extern Mix_Chunk* reverse_sound;
extern Mix_Chunk* eatable_sound;
extern Mix_Music*gameover_sound;
bool LoadMusic();
void CloseMusic();

#endif
