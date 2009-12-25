/*
 *  newgamenode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __NEWGAMENODE_H__
#define __NEWGAMENODE_H__

#include "node.h"

class NewGameNode: public Node
{
public:
	NewGameNode(Screen *screen);
	
	void onclick();
};

#endif
