/*
 *  mysdl.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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
