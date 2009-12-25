/*
 *  highscoremanager.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <iomanip>

#include "highscoremanager.h"

using std::fstream;
using std::ofstream;

HighscoreManager::HighscoreManager()
{
	
}

void HighscoreManager::load()
{
	return;
	fstream fs("scores", fstream::in | fstream::binary);
	
	if ( fs.is_open() )
	{
		Highscore hs, *hsobj;
		while ( fs.read((char *) &hs, sizeof hs) )
		{
			std::cout << "loading" << std::endl;
			hsobj = new Highscore;
			*hsobj = hs;
			_scores.push_back(hsobj);
		}
		
		fs.close();
	}
	else
	{
		std::cout << "error" << std::endl;
	}
}

void HighscoreManager::save()
{
	return;
	ofstream fs("scores", fstream::out | fstream::binary | fstream::trunc | fstream::app);
	
	if ( fs.fail() )
	{
		std::cout << "woowow" << std::endl;
	}
	
	if ( fs.is_open() )
	{
		for ( highscore_list::iterator iter = _scores.begin(); iter != _scores.end(); iter++ )
		{
			std::cout << "Writing" << std::endl;
			Highscore hs = (**iter);
			fs.write((char *) &hs, sizeof hs);
			std::cout << fs << std::endl;
		}
	}
	else
	{
		std::cout << "die" << std::endl;
	}
	
	fs.close();
}

void HighscoreManager::add(Highscore &score)
{
	Highscore *s = new Highscore;
	*s = score;
	_scores.push_back(s);
	std::cout << "added" << std::endl;
}
