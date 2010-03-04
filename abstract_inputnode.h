/*
 *  abstract_inputnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-03-04.
 *  Copyright 2010 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __ABSTRACT_INPUTNODE_H__
#define __ABSTRACT_INPUTNODE_H__

#include "node.h"

class Screen;

namespace Abstract
{
	class InputNode: public Node
	{
	private:
		SDL_Surface *_cursor;
		SDL_Rect _cursor_rect;
		
		TTF_Font *_font;
		SDL_Color _foreground;
		
		int _curr_index;
		
		void renderText();
	protected:
		Uint16 _str[40];
		
		void init();
		void addChar(Uint16 code, SDLKey k);
		void loadFont(int size, Uint16 r, Uint16 g, Uint16 b);
	public:
		InputNode(Screen *screen);		
		void draw(SDL_Surface *);
		
		// Methods that can be overwritten
		void onfocus() {};
		void onblur() {};
		void submit() {};
		void onclick() {};
		void ontype(Uint16, SDLKey) {};
		
		// String handling
		void str(const char* s);
		void empty();
	};
}

#endif
