/*
 *  highscoremanager.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
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

#ifndef __HIGHSCOREMANAGER_H__
#define __HIGHSCOREMANAGER_H__

#include <iostream>
#include <list>
#include <algorithm>

#include "SDL.h"

const long HIGHSCORES_SAVED = 50;

struct Highscore
{
	long score;
	Uint16 name[40];
};

typedef std::list<Highscore *> highscore_list;

bool inline comp_highscore(Highscore *one, Highscore *two)
{
	return one->score > two->score;
}

class HighscoreManager
{
private:
	highscore_list _scores;
public:
	HighscoreManager();
	void load();
	highscore_list &get() { return _scores; }
	void save();
	void add(Highscore &score);

	bool isHighscore(long score);
};

#endif
