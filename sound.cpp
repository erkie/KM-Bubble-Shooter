/*
 *  sound.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "SDL_mixer/SDL_mixer.h"
#include "sound.h"

void play_ball_bounce()
{
	static Mix_Chunk *sound = Mix_LoadWAV("bing.wav");
	Mix_PlayChannel(-1, sound, 0);
}

void play_ball_thud()
{
	static Mix_Chunk *sound = Mix_LoadWAV("thud.wav");
	Mix_PlayChannel(-1, sound, 0);
}

void play_ball_die()
{
	static Mix_Chunk *sound = Mix_LoadWAV("die.wav");
	Mix_PlayChannel(-1, sound, 0);
}

void play_lose()
{
	static Mix_Chunk *sound = Mix_LoadWAV("no.wav");
	Mix_PlayChannel(-1, sound, 0);
}

void play_win()
{
	static Mix_Chunk *sound = Mix_LoadWAV("hurray.wav");
	if ( ! sound )
		std::cout << Mix_GetError();
	Mix_PlayChannel(-1, sound, 0);
}