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

	_pos = _image->clip_rect;
	_pos.x = 0;
	_pos.y = 10;
}

void ContinueNode::onclick()
{
	_screen->game()->start();
}
