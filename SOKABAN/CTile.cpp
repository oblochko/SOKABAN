#include "CTile.h"

CTile::CTile() {
	TileID = 0;
	TileCache();
}

bool CTile::OnDraw_Rend(SDL_Renderer* ren, int X, int Y)
{
	SDL_Texture* texture;
	int x = X * 64, y = Y * 64;
	string str;
	switch (TileID)
	{
	case 0: str = loadBlock[0]; break;
	case 1: str = loadBlock[1]; break;
	case 2: str = loadBlock[2]; break;
	case 3: str = loadBlock[3]; break;
	case 4: str = loadBlock[4]; break;
	}
	texture = CSurface::onLoad(str.c_str(), ren);
	if (texture == NULL) {
		cout << "Can't create texture from surface: " << SDL_GetError() << endl;
	}

	CSurface::onDraw(ren, texture, x, y, 64);

	SDL_DestroyTexture(texture);

	//SDL_Surface* Surf_Dest = SDL_LoadBMP(str.c_str());

	//SDL_BlitSurface(Surf_Dest, NULL, Surf_Src, &DestR);

	//SDL_Flip(Surf_Src);

	return true;

}

void CTile::TileCache()
{
	loadBlock[0] = "texture/none.bmp";
	loadBlock[1] = "texture/wall.bmp";
	loadBlock[2] = "texture/box.bmp";
	loadBlock[3] = "texture/finishPoint.bmp";
	loadBlock[4] = "texture/redBox.bmp";
}
