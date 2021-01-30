#include "CMap.h"

CMap CMap::MapControl;

CMap::CMap() {
	Surf_Tileset = NULL;
	MAP_WIDTH = CLevel::width;
	MAP_HEIGHT = CLevel::height;
}

void CMap::acceptWH()
{
	MAP_WIDTH = CLevel::width;
	MAP_HEIGHT = CLevel::height;
	cout << endl << MAP_WIDTH << " " << MAP_HEIGHT << endl;
}

bool CMap::OnLoad(void)
{
	ifstream fin("map/level1.txt");
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		CTile tempTitle;
		fin >> tempTitle.TileID;
		//cout << tempTitle.TileID << endl;
		TileList.push_back(tempTitle);
	}
	return true;
}

bool CMap::OnLoad(const char* File)
{
	ifstream fin(File);
	//ifstream fin("map/level2.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "File not open" << endl;
	else
		cout << "File open" << endl;
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		CTile tempTitle;
		fin >> tempTitle.TileID;
		//cout << tempTitle.TileID << endl;
		TileList.push_back(tempTitle);
	}
	return true;
}

void CMap::OnRender(SDL_Renderer* ren, int MapX, int MapY) {
	int ID = 0;
	//cout << "map" << endl;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TileID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}
			TileList[ID].OnDraw_Rend(ren, X, Y);
			//SDL_RenderPresent(ren);
			//SDL_Flip(Surf_Display);

			ID++;
		}
	}
}

bool CMap::clear(SDL_Renderer* ren) {
	int ID = 0;
	//cout << "map" << endl;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TileID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}
			TileList[ID].TileID = TILE_TYPE_NONE;
			TileList[ID].OnDraw_Rend(ren, X, Y);
			
			//SDL_RenderPresent(ren);
			//SDL_Flip(Surf_Display);

			ID++;
		}
	}

	return true;
}

int CMap::GetTileType(float cX, float cY)
{
	int X = cX / TILE_SIZE;
	int Y = cY / TILE_SIZE;

	int ID = X + Y * MAP_WIDTH;
	int K = TileList[ID].TileID;
	//printf("%d", K);
	return TileList[ID].TileID;
}


int CMap::GetTileID(float cX, float cY)
{
	int X = cX / TILE_SIZE;
	int Y = cY / TILE_SIZE;

	int ID = X + Y * MAP_WIDTH;
	return ID;
}

void CMap::vectorShow()
{
	int ID = 0;
	cout << endl;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			cout << TileList[ID].TileID << " ";
			ID++;
		}
		cout << endl;
	}
}
