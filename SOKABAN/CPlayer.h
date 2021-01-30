#pragma once

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include <iostream>
#include <map>
#include <fstream>

#include <SDL.h>

#include "CSurface.h"

using namespace std;

class CPlayer
{
private:
	SDL_Texture* texture_none;
	map <int, string> texPers;
public:
	float X, Y;
	int moveTile;
	float delX, delY;
	int currentFrame;
	bool flagMove;
	bool pull;
public:
	CPlayer();
	void onMove(float x, float y);
	void resultMove(bool flag);
	bool onLoad(SDL_Renderer* ren);
	bool onLoad(char* FILE, SDL_Surface* Surf_C, int X, int Y, int Width, int Height, int MaxFrame);
	void onLoop();
	bool getCollision(float cX, float cY, float cWidth, float cHeight);
	void onRender(SDL_Renderer* ren);
	void cashePlayer();

};

#endif // _CPLAYER_H_

