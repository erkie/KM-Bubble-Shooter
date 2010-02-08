/*
 *  debug.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-18.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <iostream>
#include "SDL.h"

void print_pixel_at(const char *name, SDL_Surface *surface, int x, int y);

std::ostream & operator<<(std::ostream &os, const SDL_Rect &r );

#endif
