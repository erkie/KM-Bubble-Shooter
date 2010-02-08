/*
 *  grid.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-11.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <list>

#include "game.h"
#include "grid.h"

Grid::Grid(Game *game): Sprite(game), _remove_top(NULL) {}

void Grid::tick()
{
	if ( _game->isPaused() )
		return;
	
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
		(*iter)->tick();
	
	// Draw removable balls
	for ( ball_list::iterator iter = _remove_list.begin(); iter != _remove_list.end(); iter++ )
		(*iter)->tick();
	
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

void Grid::draw()
{
	if ( _game->isPaused() )
		return;
	
	// Draw my balls
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
		(*iter)->draw();
	
	// Draw removable balls
	for ( ball_list::iterator iter = _remove_list.begin(); iter != _remove_list.end(); iter++ )
		(*iter)->draw();
	
	// Draw animated *bam*
	if ( _remove_top )
		_remove_top->draw();
}

void Grid::removeBall(Ball *ball)
{
	_game->removeSprite(ball);
	delete ball;
	
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
}

void Grid::generateRow(int rows = 1)
{
	for ( ball_list::iterator iter = _balls.begin(); iter != _balls.end(); iter++ )
		(**iter).gridY((**iter).gridY() + rows);
	
	for ( int y = 0; y < rows; y++ )
		for ( int x = 0; x < BALL_GRID_W; x++ )
		{
			Ball *ball = new Ball(_game);
			ball->setState(Ball::Pinned);
			ball->gridX(x);
			ball->gridY(y);
		
			_balls.push_back(ball);
		}
}

void Grid::generateStartRows()
{
	generateRow(BALL_GRID_H / 2);
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
		{
			islands.push_back(result);
		}
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
