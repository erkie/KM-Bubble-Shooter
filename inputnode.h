/*
 *  inputnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */


#ifndef __INPUTNODE_H__
#define __INPUTNODE_H__

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "node.h"

class Screen;

class InputNode: public Node
{
private:
	SDL_Surface *_text;
	TTF_Font *_font;
	
	SDL_Color _foreground;
	
	Uint16 _str[40];
	int _curr_index;
public:
	InputNode(Screen *screen);
	void renderText();
	void draw(SDL_Surface *);
	void onclick();
	void ontype(Uint16, SDLKey);
	void submit();
};

#endif
