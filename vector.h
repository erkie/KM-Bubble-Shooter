/*
 *  vector.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-30.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
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
