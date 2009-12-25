/*
 *  highscorenode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __HIGHSCORENODE_H__
#define __HIGHSCORENODE_H__

#include "node.h"

class Screen;

class HighscoreNode: public Node
{
public:
	HighscoreNode(Screen *);
};

#endif
