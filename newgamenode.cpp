/*
 *  newgamenode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL_image/SDL_image.h"

#include "game.h"
#include "screen.h"
#include "newgamenode.h"

NewGameNode::NewGameNode(Screen *screen): Node(screen)
{
	_image = IMG_Load("menu-restart.png");
	
	_pos = _image->clip_rect;
	_pos.x = 0;
	_pos.y = 50;
}

void NewGameNode::onclick()
{
	_screen->game()->start();
	_screen->game()->reset();
}
