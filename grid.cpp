/*
 *  grid.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-11.
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

#include <list>

#include "ballmanager.h"

#include "arrow.h"
#include "game.h"
#include "grid.h"

Grid::Grid(Game *game): Sprite(game), _remove_top(NULL) {}

void Grid::tick()
{	
	if ( ! _remove_top )
	{
		_remove_top = _remove_list.front();
		if ( _remove_top )
		{
			_remove_top->bam();
			_remove_list.remove(_remove_top);
		}
		else
		{
			_game->startPointsAdding();
		}
	}
	
	if ( _remove_top )
	{
		_remove_top->tick();
		if ( ! _remove_top->_anim.isRunning() )
		{
			if ( _remove_top->wasDangly() )
				_game->addPointsJumbo();
			else
				_game->addPointsNormal();
			
			removeBall(_remove_top);
			_remove_top = NULL;
		}
	}
}

void Grid::draw() {}

void Grid::removeBall(Ball *ball)
{
	_game->removeSprite(ball);
	
	_game->arrow()->checkQueueColors();
	
	if ( _balls.size() == 0 )
	{
		_game->win();
	}
}

void Grid::addBall(Ball *ball)
{
	_balls.push_back(ball);
	
	locateGroups(*ball);
	handleDanglies();
	
	_game->checkRowCount();
}

void Grid::removeBalls(ball_list &balls)
{
	for ( ball_list::iterator iter = balls.begin(); iter != balls.end(); iter++ )
	{
		_balls.remove(*iter);
		_remove_list.push_back(*iter);
	}
	
	// We have to make sure that every color
	// in the queue actually exists on the field
	BallManager::prepRemList(this);
}

void Grid::generateRow(int rows = 1, bool is_startrow = false)
{
	// Move old balls up a Y-coordinate
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
		(**iter).gridY((**iter).gridY() + rows);
	
	for ( int y = 0; y < rows; y++ )
		for ( int x = 0; x < BALL_GRID_W; x++ )
		{
			Ball *ball = Ball::create(_game);
			if ( ! is_startrow )
				ball->setRemainingColor();
			ball->setState(Ball::Pinned);
			ball->gridX(x);
			ball->gridY(y);
		
			_balls.push_back(ball);
		}
}

void Grid::generateStartRows()
{
	generateRow(BALL_GRID_H / 2, true);
}

int Grid::countRows()
{
	int rows = 0;
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
		rows = (**iter).gridY() > rows ? (**iter).gridY() : rows;
	return rows;
}

void Grid::emptyRows()
{
	// Delete ball
	for ( ball_list::iterator ball = _balls.begin(); ball != _balls.end(); ball++ )
		removeBall(*ball);
	
	_balls.erase(_balls.begin(), _balls.end());
}

Ball* Grid::inCollision(Ball &ball)
{
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
	{
		if ( ball.collidesWith((**iter)) )
			return *iter;
	}
	return NULL;
}

bool Grid::hasBallOn(int x, int y)
{
	return getBallOn(x, y) != NULL;
}

Ball *Grid::getBallOn(int x, int y)
{
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
	{
		if ( (**iter).gridX() == x && (**iter).gridY() == y )
			return *iter;
	}
	return NULL;
}

Ball *Grid::getBallWithColor(int x, int y, Ball::Colors color)
{
	Ball *match = getBallOn(x, y);
	if ( match == NULL || match->_color != color )
		return NULL;
	return match;
}

void Grid::locateGroups(Ball &relativeTo)
{
	ball_list found;
	search(relativeTo, found);
	
	if ( found.size() >= ADJACENT_BALLS )
		removeBalls(found);
	else
		_game->decrementLives();
}

void Grid::search(Ball &ball, ball_list &result)
{
	grid_list searched;
	doSearch(ball, result, searched, true, true);
	
	// Delete everything in searched list
	for ( grid_list::iterator iter = searched.begin(); iter != searched.end(); iter++ )
		delete *iter;
}

void Grid::handleDanglies()
{
	grid_list searched;
	
	typedef std::list<ball_list*> island_list;
	island_list islands;
	
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
	{
		ball_list *result = new ball_list;
		if ( doSearch((**iter), *result, searched, true, false) )
			islands.push_back(result);
		else
			delete result;
	}
	
	for ( island_list::iterator iter = islands.begin(); iter != islands.end(); iter++ )
	{
		bool is_connected = false;
		ball_list *balls = (*iter);
		
		for ( ball_list::iterator i = balls->begin(); i != balls->end(); i++ )
			if ( (**i).gridY() == 0 )
				is_connected = true;
		
		if ( ! is_connected )
		{
			for ( ball_list::iterator iter = balls->begin(); iter != balls->end(); iter++ )
				(**iter).wasDangly(true);
			removeBalls(*balls);
		}
		
		delete balls;
	}
	
	// Delete everything in searched list
	for ( grid_list::iterator iter = searched.begin(); iter != searched.end(); iter++ )
		delete *iter;
}

// Will return true if anything was searched at all.
// the elements in searched has to be deleted after using
bool Grid::doSearch(Ball &ball, ball_list &result, grid_list &searched, bool recursive, bool use_color)
{
	/*
	 * Search:
	 *    (x+1, y-1): 1
	 *    (x,   y-1): 2
	 *    (x-1, y):   3
	 *    (x+1, y):   4
	 *    (x+1, y+1): 5
	 *    (x,   y+1): 6
	 */
	
	int x = ball.gridX(), y = ball.gridY();
	Ball::Colors c = ball._color;
	
	int even_x = ((y % 2) ? 1 : -1);
	
	int paths[7][2] = {
		{ even_x, -1}, // 1
		{ 0, -1}, // 2
		{-1,  0}, // 3
		{ 1,  0}, // 4
		{ even_x,  1}, // 5
		{ 0,  1},  // 6,
		{ 0,  0} // Me
	};
	
	bool did_search = false;
	for ( int i = 0; i < 7; i++ )
	{
		int px = paths[i][0] + x,
		    py = paths[i][1] + y;
		
		// We don't need to search something we have already searched
		if ( gridListHas(searched, px, py) ) continue;
		
		did_search = true;
		
		GridPos *grid_pos = new GridPos(px, py);
		searched.push_back(grid_pos);		
		
		Ball *match;
		if ( use_color )
			match = getBallWithColor(px, py, c);
		else
			match = getBallOn(px, py);
		
		if ( match )
		{
			result.push_back(match);
			if ( recursive )
				doSearch(*match, result, searched, recursive, use_color);
		}
	}
	return did_search;
}

bool Grid::gridListHas(grid_list &list, int grid_x, int grid_y)
{
	for ( grid_list::iterator iter = list.begin(); iter != list.end(); iter++ )
	{
		if ( (**iter).x == grid_x && (**iter).y == grid_y )
			return true;
	}
	return false;
}
