/*
 *  fx.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-13.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include "SDL.h"

#include "fx.h"

Fx::Fx(double(*trans)(double)): _transition(trans), _is_running(false)
{
	
}

void Fx::start()
{
	_start_time = SDL_GetTicks();
	_is_running = true;
}

double Fx::step()
{
	Uint32 time = SDL_GetTicks();
	double time_delta = (time - _start_time) / _duration;
	if ( _mode == Tween )
	{
		if ( time_delta >= 1 )
		{
			stop();
			return _to;
		}
		double delta = _transition(time_delta);
		return (_to - _from) * delta + _from;
	}
	else if ( _mode == Single )
	{
		if ( time_delta >= 1 )
		{
			stop();
			return _value * _transition(1);
		}
		return _value * _transition(time_delta);
	}
	return -1;
}

void Fx::stop()
{
	_is_running = false;
}

/*void foo()
{
	Fx anim(Fx::pow);
	anim.value(100, 200);
	anim.duration(500);
	
	anim.start();
	double value = anim.step();
	
	std::cout << value << std::endl;
}*/
