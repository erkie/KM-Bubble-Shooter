/*
 *  unicode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-02-16.
 *  Copyright 2010 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include "unicode.h"

using std::cout;
using std::endl;

int uni_length(const Uint16 *text)
{
	for ( int i = 0; true; i++ )
		if ( text[i] == '\0' )
			return i;
	
	return sizeof(text) - 1;
}

void uni_place(Uint16 *text, Uint16 ch, int arr_size, int index)
{
	if ( index >= arr_size - 1 || index < 0 )
		return;
	
	// Move everything back one step
	for ( int i = arr_size - 3; i >= index; i-- )
		text[i + 1] = text[i];
	
	// Add back removed null byte character from end
	text[arr_size - 1] = '\0';
	
	// Insert new character
	text[index] = ch;
}

void uni_slice(Uint16 *text, int arr_size, int index)
{
	if ( index >= arr_size - 1 || index < 0 )
		return;
	
	for ( int i = index; i < arr_size - 1; i++ )
	{
		text[i] = text[i + 1];
	}
	text[arr_size - 1] = '\0';
}
