#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <thread>
#include <chrono>

#include <SDL.h>
//#include <SDL2/SDL_ttf.h>


#define SCREEN_HEIGHT 820
#define SCREEN_WIDTH  820

#include "SceneManager.h"

using namespace std;

class Game
{
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Surface* screen;
	SDL_Texture* texture;

	SceneManager SManager;

	void GameProcess(SDL_Event& event);
	void Render();
	void Load(bool& run);
public:
	Game();
	void start();
};

#endif
