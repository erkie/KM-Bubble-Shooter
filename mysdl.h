/*
 *  mysdl.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
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
 *  things_that_sdl_should_do_by_default
 */

#ifndef __MYSDL_H__
#define __MYSQL_H__

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

void draw_transparent_surface_onto_empty_surface(SDL_Rect src_rect, SDL_Surface *empty, SDL_Surface *src);
SDL_Surface *change_opacity_of_surface(SDL_Surface *src, Uint8 opacity);

bool check_rect_collision(SDL_Rect *rect, int x, int y);

TTF_Font *load_font(int size);

SDL_Rect get_rect_intersection(SDL_Rect one, SDL_Rect two);

#endif
