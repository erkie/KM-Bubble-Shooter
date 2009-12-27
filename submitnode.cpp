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
	_xpos = 1;
	_ypos = 113;
	_w = 96;
	_h = 33;
}

void SubmitNode::onclick()
{
	((HighscoreScreen *)_screen)->submit();
}
