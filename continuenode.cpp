/*
 *  continuenode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL_image/SDL_image.h"

#include "game.h"
#include "screen.h"
#include "continuenode.h"

ContinueNode::ContinueNode(Screen *screen): Node(screen)
{
	_image = IMG_Load("menu-resume.png");
	
	_xpos = 0;
	_ypos = 10;
	_w = _image->clip_rect.w;
	_h = _image->clip_rect.h;
}

void ContinueNode::onclick()
{
	_screen->game()->start();
}
