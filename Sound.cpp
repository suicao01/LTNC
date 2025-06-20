#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.h"

using namespace std;

Mix_Music* background_music = NULL;

Mix_Chunk* selected_sound = NULL;
Mix_Chunk* reverse_sound = NULL;
Mix_Chunk* eatable_sound = NULL;
Mix_Music*gameover_sound=NULL;
bool LoadMusic()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cerr << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2408) == -1)
	{
		cerr << "Error:" << Mix_GetError() << endl;
		success = false;
	}
	background_music = Mix_LoadMUS("assets/music.ogg");
	if (background_music == NULL)
	{
		cerr << "Failed to load background music! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	selected_sound = Mix_LoadWAV("assets/gamestart.ogg");
	if (selected_sound == NULL)
	{
		cerr << "Failed to load selected sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}

	reverse_sound = Mix_LoadWAV("assets/match1.ogg");
	if (reverse_sound == NULL)
	{
		cerr << "Failed to load reverse sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}

	eatable_sound = Mix_LoadWAV("assets/match3.ogg");
	if (eatable_sound == NULL)
	{
		cerr << "Failed to load eat sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	gameover_sound = Mix_LoadMUS("assets/gameover.ogg");
	if (gameover_sound == NULL)
	{
		cerr << "Failed to load background music! SDL_mixer Error: %s\n" << Mix_GetError();
		success = false;
	}
	return success;
}
void CloseMusic()
{
	Mix_FreeChunk(eatable_sound);
	Mix_FreeChunk(reverse_sound);
	Mix_FreeChunk(selected_sound);
	Mix_FreeMusic(gameover_sound);
	eatable_sound = NULL;
	reverse_sound = NULL;
	selected_sound = NULL;

	Mix_FreeMusic(background_music);
	background_music = NULL;
	gameover_sound=NULL;
	Mix_Quit();
}
