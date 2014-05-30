/*
 *  screen.h
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

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <list>
#include "SDL.h"

class Node;
class Menu;
class Game;

class Screen
{
protected:
	SDL_Rect _pos;

	typedef std::list<Node*> node_list;
	node_list _nodes;

	Node *_focus_node;
	Menu *_menu;

	bool _is_dragging;
public:
	enum Events {Click, Hover, Type, Scroll, Show, Down, Move};

	Screen(Menu *menu): _menu(menu), _focus_node(NULL), _is_dragging(false) {};
	~Screen();

	void addNode(Node *node);
	virtual void draw(SDL_Surface *) = 0;
	void drawNodes(SDL_Surface *);

	SDL_Rect makeRect(SDL_Rect r);

	void fireEvent(Events type, const SDL_Event &event);
	void fireEvent(Events type);
	Node *getNodeOn(int x, int y);

	Game *game();
	Menu *menu() { return _menu; }
};

#endif
