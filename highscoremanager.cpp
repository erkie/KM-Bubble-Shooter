/*
 *  highscoremanager.cpp
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

#include <iostream>
#include <fstream>
#include <iomanip>
#include <iomanip>

#include "highscoremanager.h"

using std::fstream;
using std::ofstream;

HighscoreManager::HighscoreManager() {}

void HighscoreManager::load()
{
	// First we clear all old scores
	for ( highscore_list::iterator iter = _scores.begin(); iter != _scores.end(); iter++ )
		delete (*iter);

	fstream fs("scores", fstream::in);

	if ( fs.is_open() )
	{
		Highscore hs, *hsobj;
		while ( fs.read((char *) &hs, sizeof hs) )
		{
			hsobj = new Highscore;
			*hsobj = hs;
			_scores.push_back(hsobj);
		}

		fs.close();
	}

	_scores.sort(comp_highscore);
}

void HighscoreManager::save()
{
	ofstream fs("scores", fstream::trunc);

	if ( fs.is_open() )
	{
		for ( highscore_list::iterator iter = _scores.begin(); iter != _scores.end(); iter++ )
		{
			Highscore hs = (**iter);
			fs.write((char *) &hs, sizeof hs);
		}
	}

	fs.close();
}

void HighscoreManager::add(Highscore &score)
{
	Highscore *s = new Highscore;
	*s = score;

	_scores.push_back(s);

	_scores.sort(comp_highscore);

	if ( _scores.size() >= HIGHSCORES_SAVED )
	{
		// Remove last score
		Highscore *old = _scores.back();
		_scores.pop_back();

		delete old;
	}
}

bool HighscoreManager::isHighscore(long score)
{
	if ( _scores.size() < HIGHSCORES_SAVED )
		return true;

	_scores.sort(comp_highscore);
	highscore_list::iterator iter = _scores.begin();
	advance(iter, HIGHSCORES_SAVED - 1); // Go to last score

	if ( score > (*iter)->score )
		return true;
	return false;
}
