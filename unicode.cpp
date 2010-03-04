/*
 *  unicode.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2010-02-16.
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
