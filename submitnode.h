/*
 *  submitnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */


#ifndef __SUBMITNODE_H__
#define __SUBMITNODE_H__

#include "node.h"

class Screen;

class SubmitNode: public Node
{
public:
	SubmitNode(Screen *);
	void onclick();
};

#endif
