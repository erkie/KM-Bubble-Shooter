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

#include "abstract_inputnode.h"

class Screen;

class InputNode: public Abstract::InputNode
{
public:
	InputNode(Screen *screen);
	
	void onclick();
	void ontype(Uint16, SDLKey);
	void onfocus();
	void onblur();
	void submit();
};

#endif
