#include "CSurface.h"

SDL_Texture* CSurface::tex_clear = NULL;

SDL_Texture* CSurface::onLoad(const char* File, SDL_Renderer* ren) {
	SDL_Texture* texture;
	SDL_Surface* temp_surf = NULL;
	temp_surf = SDL_LoadBMP(File);
	if (temp_surf == NULL) {
		cout << "Can't load image: " << SDL_GetError() << endl;
	}

	SDL_SetColorKey(temp_surf, SDL_TRUE, SDL_MapRGB(temp_surf->format, 255, 255, 255));

	texture = SDL_CreateTextureFromSurface(ren, temp_surf);
	if (texture == NULL) {
		cout << "Can't create texture from surface: " << SDL_GetError() << endl;
	}

	SDL_FreeSurface(temp_surf);

	return texture;
}

bool CSurface::onDraw(SDL_Renderer* ren, SDL_Texture* texture, int X, int Y, int block_size) {

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.h = DestR.w = block_size;

	SDL_RenderCopy(ren, texture, NULL, &DestR);

	return true;
}

bool CSurface::onDraw(SDL_Renderer* ren, SDL_Texture* texture, int X, int Y, int width, int height)
{
	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.h = height;
	DestR.w = width;

	SDL_RenderCopy(ren, texture, NULL, &DestR);

	return true;
}

