/*
 *  screen.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright (c) 2010 Erik Andersson
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
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
		(*iter)->draw(surface);
}

void Screen::fireEvent(Events type, const SDL_Event &event)
{
	switch ( type )
	{
		case Down:
			{
				// Get focused node
				Node *node = getNodeOn(event.button.x - _pos.x, event.button.y - _pos.y);
				// If it isn't the current node the old focused node is blurred
				if ( node != _focus_node && _focus_node != NULL )
				{
					_focus_node->focus(false);
					_focus_node->onblur();
				}
				// If focus_node is NULL empty space was clicked
				_focus_node = (node) ? node : NULL;
				// Focus event
				if ( _focus_node )
				{
					_focus_node->focus(true);
					_focus_node->onfocus();
				}
				
				_is_dragging = true;
			}
			break;
		
		case Scroll:
			if ( _focus_node )
				_focus_node->onscroll(event.button.button == SDL_BUTTON_WHEELUP);
			break;
		
		case Move:
			if ( _is_dragging && _focus_node )
			{
				_focus_node->ondrag(event.motion.xrel, event.motion.yrel);
			}
			break;
		
		case Type:
			if ( _focus_node )
			{
				Uint16 key = event.key.keysym.unicode;
				_focus_node->ontype(key, event.key.keysym.sym);
			}
			break;
			
		case Click:
			if ( _focus_node )
				_focus_node->onclick();
			_is_dragging = false;
			break;
	}
}

void Screen::fireEvent(Events type)
{
	switch ( type )
	{
		case Show:
			_focus_node = NULL;
			for ( node_list::iterator iter = _nodes.begin(); iter != _nodes.end(); iter++)
				(*iter)->onshow();
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

SDL_Rect Screen::makeRect(SDL_Rect r)
{
	r.x += _pos.x;
	r.y += _pos.y;
	return r;
}

Screen::~Screen()
{
	for ( node_list::iterator iter = _nodes.begin(); iter != _nodes.end(); iter++ )
		delete (*iter);
}
