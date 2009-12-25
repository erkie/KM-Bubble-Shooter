/*
 *  debug.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-18.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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
