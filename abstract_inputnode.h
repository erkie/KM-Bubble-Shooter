/*
 *  abstract_inputnode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-03-04.
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
