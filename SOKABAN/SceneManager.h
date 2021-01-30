#pragma once

#ifndef _SCENEMANEGER_H_
#define _SCENEMANEGER_H_

#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>

#include <SDL.h>
//#include <SDL2/SDL_ttf.h>

#include "CMap.h"
#include "CPlayer.h"
#include "CSurface.h"
#include "CLevel.h"

using namespace std;

class SceneManager
{
private:
	SDL_Surface* src_scene;
	SDL_Surface* win_scene;
	SDL_Texture* texture_clear_none;
	SDL_Texture* texture_clear_finish;
	SDL_Texture* texture_clear_redBox;
	SDL_Texture* texture_clear_box;
	SDL_Texture* texture_end_game;
	SDL_Texture* texture_pull_on;
	SDL_Texture* texture_pull_off;
	SDL_Texture* texture_help_one;
	SDL_Texture* texture_help_two;
	//* texture
public:
	SceneManager();
	void update(const SDL_Event& event, SDL_Renderer* ren);
	SDL_Texture* render(SDL_Renderer* ren);
	void load(SDL_Renderer* ren);
	void load(SDL_Renderer* ren, bool &_run);
private:
	bool processEvents(const SDL_Event& event, SDL_Renderer* ren);
	void detectCollisions(SDL_Renderer* ren);
	void onPull(SDL_Renderer* ren);
	void offPull(SDL_Renderer* ren);
	void casheTextureClear(SDL_Renderer* ren);
	void reset(SDL_Renderer* ren);
	bool isEnd();
	void changeLevelToNext(SDL_Renderer* ren);
	void exitGame(SDL_Renderer* ren);
private:
	CLevel lvl;
	CPlayer player;
	CMap rmap;
public:
	bool run;
};

#endif
