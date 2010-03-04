/*
 *  debug.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-18.
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

#include <cstdio>
#include "debug.h"

void print_pixel_at(const char *name, SDL_Surface *surface, int x, int y)
{
	/* Extracting color components from a 32-bit color value */
	SDL_PixelFormat *fmt;
	Uint32 temp, pixel;
	Uint8 red, green, blue, alpha;
	
	fmt = surface->format;
	SDL_LockSurface(surface);
	pixel = *((Uint32*)surface->pixels) + x + y;
	SDL_UnlockSurface(surface);
	
	/* Get Red component */
	temp = pixel & fmt->Rmask;  /* Isolate red component */
	temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
	red = (Uint8)temp;
	
	/* Get Green component */
	temp = pixel & fmt->Gmask;  /* Isolate green component */
	temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
	green = (Uint8)temp;
	
	/* Get Blue component */
	temp = pixel & fmt->Bmask;  /* Isolate blue component */
	temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
	blue = (Uint8)temp;
	
	/* Get Alpha component */
	temp = pixel & fmt->Amask;  /* Isolate alpha component */
	temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
	temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
	alpha = (Uint8)temp;
	
	printf("Pixel Color (%s) -> R: %d,  G: %d,  B: %d,  A: %d\n", name, red, green, blue, alpha);
}

std::ostream & operator<<(std::ostream &os, const SDL_Rect &r )
{
	os << "[SDL_Rect left: " << r.x << ", top: " << r.y << ", right: " << r.x + r.w << ", bottom: " << r.y + r.h <<  ", w: " << r.w << ", h: " << r.h << "]\n";
	return os;
}
