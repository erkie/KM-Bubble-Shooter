/*
 *  sound.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright (c) 2010 Erik Andersson
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 */

#include <iostream>

#include "SDL_mixer/SDL_mixer.h"
#include "sound.h"

void play_music()
{
	static Mix_Music *sound = Mix_LoadMUS("kattMickisShooter.ogg");
	Mix_PlayMusic(sound, -1);
}

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