#include "CPlayer.h"

CPlayer::CPlayer()
{
	//    textur_pers = NULL;
	X = 64;
	Y = 64;
	moveTile = 0;
	delX = delY = 0;
	currentFrame = 0;
	flagMove = 0;
	pull = false;
	texture_none = NULL;
	cashePlayer();
}

bool CPlayer::onLoad(SDL_Renderer* ren)
{
	texture_none = CSurface::onLoad(texPers[4].c_str(), ren);
	if (!texture_none) return false;
}

void CPlayer::cashePlayer()
{
	texPers[0] = "texture/player/playerDown.bmp";
	texPers[1] = "texture/player/playerLeft.bmp";
	texPers[2] = "texture/player/playerRight.bmp";
	texPers[3] = "texture/player/playerUp.bmp";
	texPers[4] = "texture/none.bmp";
}

void CPlayer::onMove(float x, float y)
{
	if (x == 0 && y == 0)
	{
		delX = delY = 0;
	}
	if (x == -1)
	{
		currentFrame = 1;
		delX = -64;
		delY = 0;
		return;
	}
	if (x == 1)
	{
		currentFrame = 2;
		delX = 64;
		delY = 0;
		return;
	}
	if (y == -1)
	{
		currentFrame = 3;
		delY = -64;
		delX = 0;
		return;
	}
	if (y == 1)
	{
		currentFrame = 0;
		delY = 64;
		delX = 0;
		return;
	}
	delX = delY = 0;
}

void CPlayer::resultMove(bool flag)
{
	X += delX;
	Y += delY;
	delX = delY = 0;
}


void CPlayer::onRender(SDL_Renderer* ren)
{
	SDL_Texture* texture_pers = NULL;
	texture_pers = CSurface::onLoad(texPers[currentFrame].c_str(), ren);
	if (flagMove == 1)
	{
		//CSurface::onDraw(ren, texture_none, X, Y, 64);
		resultMove(1);
	}
	CSurface::onDraw(ren, texture_pers, X, Y, 64);
	SDL_DestroyTexture(texture_pers);
}
