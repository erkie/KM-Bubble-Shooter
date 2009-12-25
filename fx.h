/*
 *  fx.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-13.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __FX__H__
#define __FX__H__

#include "SDL.h"

class Fx
{
private:
	double _to, _from;
	double _value;
	
	double _duration;
	Uint32 _start_time;
	double(*_transition)(double);
	bool _is_running;
public:
	enum Mode {Single, Tween};
	Mode _mode;
	
	Fx(double(*trans)(double));
	Fx(): _is_running(false) {};
	
	void transition(double(*trans)(double)) { _transition = trans; };
	void mode(Mode m) { _mode = m; };
	void value(double from, double to) { _from = from; _to = to; };
	void value(double value) { _value = value; };
	
	void duration(double duration) { _duration = duration; };
	bool isRunning() { return _is_running; };
	
	void start();
	void stop();
	double step();
};

#endif
