#pragma once

#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include <iostream>
#include <fstream>

#include <SDL.h>

using namespace std;

class CSurface {
public:
	static SDL_Texture* tex_clear;
public:
	CSurface(SDL_Renderer* ren);
	static SDL_Texture* onLoad(const char* File, SDL_Renderer* ren);
	static bool onDraw(SDL_Renderer* ren, SDL_Texture* texture, int X, int Y, int block_size);
	static bool onDraw(SDL_Renderer* ren, SDL_Texture* texture, int X, int Y, int width, int height);
};

#endif
