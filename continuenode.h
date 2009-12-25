/*
 *  continuenode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __CONTINUENODE_H__
#define __CONTINUENODE_H__

#include "node.h"

class ContinueNode: public Node
{
public:
	ContinueNode(Screen *screen);
	
	void onclick();
};

#endif
