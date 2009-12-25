/*
 *  screen.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include "menu.h"
#include "node.h"
#include "screen.h"

Game *Screen::game()
{
	return _menu->game();
}

void Screen::addNode(Node *node)
{
	_nodes.push_back(node);
}

void Screen::drawNodes(SDL_Surface *surface)
{
	for ( node_list::iterator iter = _nodes.begin(); iter != _nodes.end(); iter++ )
	{
		Node *node = *iter;
		node->draw(surface);
	}
}

void Screen::fireEvent(Events type, const SDL_Event &event)
{
	switch ( type )
	{
		case Type:
			if ( _focus_node )
			{
				Uint16 key = event.key.keysym.unicode;
				_focus_node->ontype(key);
			}
			break;
			
		case Click:
			Node *node = getNodeOn(event.button.x - _pos.x, event.button.y - _pos.y);
			if ( node )
			{
				_focus_node = node;
				node->onclick();
			}
			else
				_focus_node = NULL;
			break;
	}
}

Node *Screen::getNodeOn(int x, int y)
{
	for ( node_list::iterator iter = _nodes.begin(); iter != _nodes.end(); iter++ )
		if ( (*iter)->collidesWith(x, y) )
			return (*iter);
	return NULL;
}

SDL_Rect Screen::makeRect(int x, int y)
{
	SDL_Rect rect;
	rect.x = x + _pos.x;
	rect.y = y + _pos.y;
	return rect;
}

Screen::~Screen()
{
	for ( node_list::iterator iter = _nodes.begin(); iter != _nodes.end(); iter++ )
		delete (*iter);
}
