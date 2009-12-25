/*
 *  vector.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-11-30.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>

#include "vector.h"
#include "SDL.h"

const double PI = 3.14159262;
const double RADTODEG = 180 / PI;
const double DEGTORAD = PI / 180;

Vector &Vector::operator=(Vector vec)
{
	_x = vec.x();
	_y = vec.y();
	return *this;
}

bool Vector::operator==(Vector vec)
{
	return _x == vec.x() && _y == vec.y();
}

bool Vector::operator!=(Vector vec)
{
	return _x != vec.x() || _y != vec.y();
}

Vector &Vector::operator+=(Vector vec)
{
	_x += vec.x();
	_y += vec.y();
	return *this;
}

Vector Vector::operator+(Vector vec)
{
	Vector vecx = Vector(_x + vec.x(), _y + vec.y());
	return Vector(_x + vec.x(), _y + vec.y());
}

Vector &Vector::operator-=(Vector vec)
{
	_x -= vec.x();
	_y -= vec.y();
	return *this;
}

Vector Vector::operator-(Vector vec)
{
	return Vector(_x - vec.x(), _y - vec.y());
}

Vector &Vector::operator*=(double scale)
{
	_x *= scale;
	_y *= scale;
	return *this;
}

Vector Vector::operator*(double scale)
{
	return Vector(_x * scale, _y * scale);
}

double Vector::dot(Vector &vec)
{
	return _x * vec.x() + _y * vec.y();
}

double Vector::length() const
{
	return sqrt(_x * _x + _y * _y);
}

double Vector::angle() const
{
	return atan2(_x, _y) * RADTODEG;
}

void Vector::angle(double deg)
{
	double r = length();
	
	_x = r * cos(deg * DEGTORAD);
	_y = r * sin(deg * DEGTORAD);
}

double Vector::angleBetween(Vector &vec)
{
	double cosAngle = dot(vec) / (length() * vec.length());
	return acos(cosAngle) * RADTODEG;
}

double Vector::angleSeparating(Vector &vec)
{
	return (*this - vec).angle();
}

double Vector::distanceBetween(Vector &vec)
{
	return sqrt(pow(_x - vec.x(), 2) + pow(_y - vec.y(), 2));
}

/*
 * Debuging
 */

SDL_Rect Vector::toRect()
{
	SDL_Rect rect;
	rect.x = _x - 3;
	rect.y = _y - 3;
	rect.w = 6;
	rect.h = 6;
	return rect;
}

void Vector::visualize(SDL_Surface *dst)
{
	SDL_Rect r = toRect();
	SDL_FillRect(dst, &r, SDL_MapRGB(dst->format, 0xFF, 0x00, 0x00));
}

std::ostream & operator<<(std::ostream &os, const Vector &V )
{
	os << "[" << V._x << ", " << V._y << "] (" << V.angle() << ", " << V.length() << ")";
	return os;
}
