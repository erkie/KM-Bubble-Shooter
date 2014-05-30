/*
 *  vector.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-30.
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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include "SDL.h"

class Vector
{
public:
	double _x, _y;

	Vector() {}
	Vector(double x, double y): _x(x), _y(y) {}
	Vector(const Vector &vec): _x(vec.x()), _y(vec.y()) {}

	double x() const { return _x; }
	double y() const { return _y; }

	void x(double x) { _x = x; }
	void y(double y) { _y = y; }

	Vector &operator=(Vector vec);
	bool operator==(Vector vec);
	bool operator!=(Vector vec);
	Vector &operator+=(Vector vec);
	Vector operator+(Vector vec);
	Vector &operator-=(Vector vec);
	Vector operator-(Vector vec);
	Vector &operator-();
	Vector operator*(double scale);
	Vector &operator*=(double scale);

	double dot(Vector &vec);

	double length() const;
	double angle() const;
	void angle(double deg);
	double angleBetween(Vector &vec);
	double angleSeparating(Vector &vec);
	double distanceBetween(Vector &vec);

	SDL_Rect toRect();
	void visualize(SDL_Surface *dst);

	void zero() { _x = _y = 0; };
	bool isZero() { return _x == 0 && _y == 0; };

	friend std::ostream & operator<<(std::ostream &os, const Vector &V);
};

#endif
