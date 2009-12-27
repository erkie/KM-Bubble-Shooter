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
	_xpos = 106;
	_ypos = 115;
	_w = 28;
	_h = 29;
}

void CancelNode::onclick()
{
	_screen->menu()->showScreen(Menu::Home);
}
