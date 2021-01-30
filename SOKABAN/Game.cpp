#include "Game.h"

Game::Game()
{
	win = NULL;
	ren = NULL;
	screen = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Can't init SDL: " << SDL_GetError() << endl;
	}

	win = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		cout << "Can't create window: " << SDL_GetError() << endl;
		//ok = false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		cout << "Can't create renderer: " << SDL_GetError() << endl;
		//ok = false;
	}

	//screen = SDL_GetWindowSurface(win);

	/*int flags = IMG_INIT_PNG;

	if ( !( IMG_Init( flags ) & flags ) ) {
		std::cout << "Can't init image: " << IMG_GetError() << std::endl;
		return false;
	}*/

	/*if (TTF_Init())
	{
		cout << "Can't create TTF: " << endl;
		//ok = false;
	}*/

	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

	//SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0xFF);
	//SDL_UpdateWindowSurface(win);

	cout << "Init Good" << endl;
}

void Game::start()
{
	bool run = true;
	SDL_Event event;
	Load(run);
	while (run)
	{
		if (run)
			Render();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			{
				run = false;
			}
			else
			{
				SManager.update(event, ren);
				if (SManager.run == false) {
					return;
				}
			}
		}
		
	}
	
}



void Game::Render()
{
	//SDL_RenderClear(ren);
	SManager.render(ren);
	SDL_RenderPresent(ren);
}

void Game::Load(bool &run)
{
	SManager.load(ren);
	SDL_RenderPresent(ren);
	//SManager.Init()
}
