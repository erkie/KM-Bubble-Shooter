/*
 *  submitnode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "SDL.h"

#include "highscorescreen.h"

#include "menu.h"
#include "screen.h"
#include "submitnode.h"

SubmitNode::SubmitNode(Screen *screen): Node(screen)
{
	_pos.x = 1;
	_pos.y = 113;
	_pos.w = 96;
	_pos.h = 33;
}

void SubmitNode::onclick()
{
	((HighscoreScreen *)_screen)->submit();
}
