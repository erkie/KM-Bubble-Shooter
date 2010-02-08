/*
 *  highscorescreen.cpp
 *  kattMickisShooter
 *
 *  Created by Erik Andersson on 2009-12-23.
 *  Copyright 2009 Åva gymnasium. All rights reserved.
 *
 */

#include <sstream>

#include "SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"

#include "mysdl.h"

// Nodes
#include "inputnode.h"
#include "cancelnode.h"
#include "submitnode.h"
#include "highscorenode.h"

#include "highscorescreen.h"

HighscoreScreen::HighscoreScreen(Menu *menu): Screen(menu), _points(NULL)
{
	for ( int i = 0; i < 40; i++ )
		_name[i] = '\0';
	
	_image = IMG_Load("highscore.png");
	
	// My position on the screen
	_pos.w = 308;
	_pos.h = 170;
	_pos.x = _menu->centerX() - _pos.w / 2;
	_pos.y = _menu->centerY() - _pos.h / 2 + 20;
	
	// Controls position relative to me 
	// Perhaps this and _text should be nodes
	_controls.x = 0 + _pos.x;
	_controls.y = 70 + _pos.y;
	
	_fg.r = _fg.g = _fg.b = 0xFF;
	
	// Create Wow! You got... text
	TTF_Font *font = load_font(16);
	_text = TTF_RenderText_Blended(font, "Wow! You got:", _fg);
	TTF_CloseFont(font);
	
	_text_rect.x = 0 + _pos.x;
	_text_rect.y = 10 + _pos.y;
	
	// Initialize X points
	_font = load_font(20);
	renderPointsText();
	
	addNode(new InputNode(this));
	addNode(new CancelNode(this));
	addNode(new SubmitNode(this));
	addNode(new HighscoreNode(this));
}

void HighscoreScreen::draw(SDL_Surface *surface)
{
	SDL_BlitSurface(_image, NULL, surface, &_controls);
	SDL_BlitSurface(_text, NULL, surface, &_text_rect);
	SDL_BlitSurface(_points, NULL, surface, &_points_rect);
	
	drawNodes(surface);
}

void HighscoreScreen::renderPointsText()
{
	if ( _points )
		SDL_FreeSurface(_points);
	
	std::stringstream text;
	text << _menu->game()->lastPoints();
	text << " points!";
	_points = TTF_RenderText_Blended(_font, text.str().c_str(), _fg);
	
	_points_rect = _text_rect;
	_points_rect.y += _text->clip_rect.h;
}

void HighscoreScreen::submit()
{
	if ( _name[0] == '\0' )
		return;
	
	Highscore hs;
	for ( int i = 0; i < 40; i++ )
		hs.name[i] = _name[i];
	hs.score = game()->lastPoints();
	menu()->manager.add(hs);
	menu()->manager.save();
	
	menu()->showScreen(Menu::Home);	
}
