#pragma once
#ifndef _CTILE_H_
#define _CTILE_H_

#include <iostream>
#include <map>
#include <string>

#include <SDL.h>

#include "CSurface.h"

using namespace std;

enum
{
	TILE_TYPE_NONE = 0,

	TILE_TYPE_WALL,
	TILE_TYPE_BOX,
	TILE_TYPE_FINISHPOINT,
	TILE_TYPE_RED_BOX
};

class CTile {
public:
	int     TileID;
	map <int, string> loadBlock;
public:
	CTile();
	bool OnDraw_Rend(SDL_Renderer* ren, int X, int Y);
	void TileCache();
};

#endif

