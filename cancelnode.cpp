/*
 *  cancelnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL.h"

#include "menu.h"
#include "screen.h"
#include "cancelnode.h"

CancelNode::CancelNode(Screen *screen): Node(screen)
{
	_pos.x = 106;
	_pos.y = 115;
	_pos.w = 28;
	_pos.h = 29;
}

void CancelNode::onclick()
{
	_screen->menu()->showScreen(Menu::Home);
}
