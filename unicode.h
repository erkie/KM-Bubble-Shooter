/*
 *  unicode.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-02-16.
 *  Copyright 2010 Åva gymnasium. All rights reserved.
 *
 *  A collection of simple unicode text operations
 */

#ifndef __UNICODE_H__
#define __UNICODE_H__

#include "SDL.h"

int uni_length(const Uint16 *text);
void uni_place(Uint16 *text, Uint16 ch, int arr_size, int index);
void uni_slice(Uint16 *text, int arr_size, int index);

#endif