/*
 *  screen.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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
public:
	enum Events {Click, Hover, Type};
	
	Screen(Menu *menu): _menu(menu), _focus_node(NULL) {};
	~Screen();
	
	void addNode(Node *node);
	virtual void draw(SDL_Surface *) = 0;
	void drawNodes(SDL_Surface *);
	
	SDL_Rect makeRect(int x, int y);
	
	void fireEvent(Events type, const SDL_Event &event);
	Node *getNodeOn(int x, int y);
	
	Game *game();
	Menu *menu() { return _menu; }
};

#endif
