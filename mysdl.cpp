/*
 *  mysdl.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-19.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>

#include "mysdl.h"

const bool USE_NATIVE_BLIT = true;

void draw_transparent_surface_onto_empty_surface(SDL_Rect src_rect, SDL_Surface *empty, SDL_Surface *src)
{	
	if ( USE_NATIVE_BLIT )
	{
		src->flags &= ~SDL_SRCALPHA;
		SDL_BlitSurface(src, &src_rect, empty, NULL);
		SDL_SetAlpha(src, SDL_SRCALPHA, 0xFF);
	}
	
	if ( ! USE_NATIVE_BLIT )
	{
		SDL_Rect size = empty->clip_rect;
		int w = size.w, h = size.h;
		
		SDL_LockSurface(empty);
		SDL_LockSurface(src);
		
		int ebpp = empty->format->BytesPerPixel,
			sbpp = src->format->BytesPerPixel;
		
		Uint8 *pixel, *color;
		
		for ( int x = 0; x < w; x++ )
			for ( int y = 0; y < h; y++ )
			{
				pixel = (Uint8 *)empty->pixels + y * empty->pitch + x * ebpp;
				color = (Uint8 *)src->pixels + (y + src_rect.y) * src->pitch + (x + src_rect.x) * sbpp;
				
				*(Uint32*)pixel = *(Uint32*)color;
			}
		
		SDL_UnlockSurface(src);
		SDL_UnlockSurface(empty);
	}
}

SDL_Surface *change_opacity_of_surface(SDL_Surface *src, Uint8 opacity)
{
	SDL_Surface *dst = SDL_DisplayFormatAlpha(src);
	
	int w = src->clip_rect.w,
		h = src->clip_rect.h;
	
	SDL_PixelFormat *fmt = src->format;
	Uint8 *pixel;
	Uint32 opacity_mask = (opacity << fmt->Ashift) & fmt->Amask | fmt->Rmask | fmt->Bmask | fmt->Gmask;
	
	SDL_LockSurface(src);
	SDL_LockSurface(dst);
	
	for ( int x = 0; x < w; x++ )
		for ( int y = 0; y < h; y++ )
		{
			pixel = (Uint8 *)dst->pixels + y * dst->pitch + x * fmt->BytesPerPixel;
			*(Uint32*)pixel = (*(Uint32*)pixel & opacity_mask);
		}
	
	SDL_UnlockSurface(dst);
	SDL_UnlockSurface(src);
	
	return dst;
}

bool check_rect_collision(SDL_Rect *rect, int x, int y)
{
	return x > rect->x && y > rect->y && x < (rect->x + rect->w) && y < (rect->y + rect->h);
}

TTF_Font *load_font(int size)
{
	TTF_Font *font = TTF_OpenFont("font.otf", size);
	if ( ! font )
	{
		std::cerr << "Could not load font: " << TTF_GetError();
		return NULL;
	}
	return font;
}

SDL_Rect get_rect_intersection(SDL_Rect one, SDL_Rect two)
{
	SDL_Rect result;
	result.x = two.x - one.x;
	result.y = two.y - one.y;
	result.w = two.w - result.x;
	result.h = two.h - result.y;
	return result;
}
