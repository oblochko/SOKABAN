#pragma once

#ifndef _CMAP_H_
#define _CMAP_H_

#include <SDL.h>
#include <vector>
#include <fstream>
#include <iostream>
//#define MAP_WIDTH 11
//#define MAP_HEIGHT 9
#define TILE_SIZE 64

#include "CTile.h"
#include "CLevel.h"

using namespace std;

class CMap {
private:
	int MAP_WIDTH;
	int MAP_HEIGHT;
public:
	static CMap MapControl;

	SDL_Surface* Surf_Tileset;

public:
	std::vector<CTile> TileList;

public:
	CMap();

public:
	bool clear(SDL_Renderer* ren);
	bool OnLoad(void);
	bool OnLoad(const char* File);
	//void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
	void OnRender(SDL_Renderer* ren, int MapX, int MapY);

	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

	int GetTileType(float cX, float cY);
	int GetTileID(float cX, float cY);
	void acceptWH();
	void vectorShow();
};

#endif

