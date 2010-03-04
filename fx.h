/*
 *  fx.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-13.
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
