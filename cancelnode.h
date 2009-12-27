/*
 *  cancelnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-26.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __CANCELNODE_H__
#define __CANCELNODE_H__

#include "node.h"

class Screen;

class CancelNode: public Node
{
public:
	CancelNode(Screen *);
	void onclick();
};

#endif
