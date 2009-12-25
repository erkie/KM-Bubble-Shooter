/*
 *  highscoremanager.h
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#ifndef __HIGHSCOREMANAGER_H__
#define __HIGHSCOREMANAGER_H__

#include <list>
#include <algorithm>

#include "SDL.h"

struct Highscore
{
	long score;
	Uint16 name[40];
};

typedef std::list<Highscore *> highscore_list;

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
};

#endif
