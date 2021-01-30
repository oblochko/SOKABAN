#include "SceneManager.h"

SceneManager::SceneManager()
{
	src_scene = NULL;
	win_scene = NULL;
	texture_clear_none = NULL;
	texture_clear_finish = NULL;
	texture_clear_redBox = NULL;
	texture_clear_box = NULL;
	texture_end_game = NULL;
	texture_pull_off = NULL;
	texture_help_one = NULL;
	texture_help_two = NULL;
	run = true;
}

void SceneManager::update(const SDL_Event& event, SDL_Renderer* ren)
{
	if (processEvents(event, ren))
	{
		detectCollisions(ren);
		//rmap.OnRender(ren, 50, 50);
		if (isEnd())
		{
			reset(ren);
			changeLevelToNext(ren);
			if (CLevel::currentLevel > CLevel::maxLevel) return;
		}
	}


}

bool SceneManager::processEvents(const SDL_Event& event, SDL_Renderer* ren)
{
	bool flag = false;
	switch (event.type)
	{
	case SDL_KEYDOWN:
	{
		// exit if ESCAPE is pressed
//if (event.key.keysym.sym == SDLK_ESCAPE)
//    done = true;
		if (event.key.keysym.sym == SDLK_LEFT) //kiborfd [i];
		{ //Player.MoveLeft = true; Player.OnLoop();
			cout << "KEY LEFT" << endl;
			player.onMove(-1, 0);
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{ //Player.MoveRight = true; Player.OnLoop();
			cout << "KEY RIGHT" << endl;
			player.onMove(1, 0);
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_UP)
		{ //Player.MoveUp = true; Player.OnLoop();
			cout << "KEY UP" << endl;
			player.onMove(0, -1);
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{ //Player.MoveDown = true; Player.OnLoop();
			cout << "KEY DOWN" << endl;
			player.onMove(0, 1);
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			CSurface::onDraw(ren, texture_clear_none, 10, CLevel::height * 64, 750, 45);
			if (player.pull) { player.pull = false; CSurface::onDraw(ren, texture_pull_off, 10, CLevel::height * 64, 750 , 45); }
			else { player.pull = true;  CSurface::onDraw(ren, texture_pull_on, 10, CLevel::height * 64, 750, 45);
			}

			cout << " FLAG " << player.pull << endl;
			
		}
		//Player.MoveLeft = Player.MoveRight = Player.MoveUp = Player.MoveDown =false;
		return flag;
	}
	case SDL_KEYUP:
	{
		if (event.key.keysym.sym == SDLK_LEFT)
		{ //Player.MoveLeft = true; Player.OnLoop();
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{ //Player.MoveLeft = true; Player.OnLoop();
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_UP)
		{ //Player.MoveLeft = true; Player.OnLoop();
			flag = true;
			return flag;
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{ //Player.MoveLeft = true; Player.OnLoop();
			flag = true;
			return flag;
		}
		return flag;
	}
	}
}

SDL_Texture* SceneManager::render(SDL_Renderer* ren)
{
	//rmap.OnRender(ren, 50, 50);
	player.onRender(ren);
	return NULL;
}

void SceneManager::load(SDL_Renderer* ren)
{
	rmap.OnLoad();
	rmap.OnRender(ren, 50, 50);
	player.onLoad(ren);
	player.onRender(ren);
	casheTextureClear(ren);
	CSurface::onDraw(ren, texture_pull_off, 10, CLevel::height * 64, 750, 50);
	CSurface::onDraw(ren, texture_help_one, 10, CLevel::height * 64 + 60, 560, 30);
	CSurface::onDraw(ren, texture_help_two, 10, CLevel::height * 64 + 95, 310, 30);
	//return texturn;
}

void SceneManager::load(SDL_Renderer* ren, bool &_run)
{
	rmap.OnLoad();
	rmap.OnRender(ren, 50, 50);
	player.onLoad(ren);
	player.onRender(ren);
	casheTextureClear(ren);
	run = _run;
	CSurface::onDraw(ren, texture_pull_off, 10, CLevel::height * 64, 750, 50);
	CSurface::onDraw(ren, texture_help_one, 10, CLevel::height * 64 + 60, 560, 30);
	CSurface::onDraw(ren, texture_help_two, 10, CLevel::height * 64 + 95, 310, 30);
	//return texturn;
}

void SceneManager::detectCollisions(SDL_Renderer* ren)
{
	if (player.pull) onPull(ren);
	else offPull(ren);
}

void SceneManager::onPull(SDL_Renderer* ren)
{
	float moveX = player.delX + player.X, moveY = player.delY + player.Y, prevX = player.X - player.delX, prevY = player.Y - player.delY;
	int tileNext = rmap.GetTileType(moveX + 32, moveY + 32);
	int tilePrev = rmap.GetTileType(prevX + 32, prevY + 32);
	if (tileNext == TILE_TYPE_NONE || tileNext == TILE_TYPE_FINISHPOINT)
	{
		player.flagMove = true;
		CSurface::onDraw(ren, texture_clear_none, player.X, player.Y, 64);
		if (rmap.GetTileType(player.X + 32, player.Y + 32) == 3) CSurface::onDraw(ren, texture_clear_finish, player.X, player.Y, 64);
		if (tilePrev == TILE_TYPE_BOX || tilePrev == TILE_TYPE_RED_BOX)
		{
			int tempTily = rmap.GetTileType(player.X + 32, player.Y + 32);
			if (tilePrev == TILE_TYPE_BOX)
			{
				//cout << "Prev title " << rmap.GetTileType(prevX, prevY);
				CSurface::onDraw(ren, texture_clear_none, prevX, prevY, 64);
				rmap.TileList[rmap.GetTileID(prevX, prevY)].TileID = 0;
				if (tempTily == TILE_TYPE_NONE) {
					CSurface::onDraw(ren, texture_clear_box, player.X, player.Y, 64);					
					rmap.TileList[rmap.GetTileID(player.X, player.Y)].TileID = 2;
				}
				else {
					CSurface::onDraw(ren, texture_clear_redBox, player.X, player.Y, 64);
					rmap.TileList[rmap.GetTileID(player.X, player.Y)].TileID = TILE_TYPE_RED_BOX;
					CLevel::kolPoint++;
				}
			}
			else
			{
				CLevel::kolPoint--;
				CSurface::onDraw(ren, texture_clear_none, prevX, prevY, 64);
				CSurface::onDraw(ren, texture_clear_finish, prevX, prevY, 64);
				rmap.TileList[rmap.GetTileID(prevX, prevY)].TileID = TILE_TYPE_FINISHPOINT;
				if (tempTily == TILE_TYPE_NONE) {
					CSurface::onDraw(ren, texture_clear_box, player.X, player.Y, 64);					
				    rmap.TileList[rmap.GetTileID(player.X, player.Y)].TileID = TILE_TYPE_BOX; 					
				}
				else {
					CSurface::onDraw(ren, texture_clear_redBox, player.X, player.Y, 64);
					rmap.TileList[rmap.GetTileID(player.X, player.Y)].TileID = TILE_TYPE_RED_BOX;
					CLevel::kolPoint++;
				}
			}
			//return;
		}
		return;
	}
	if (tileNext == TILE_TYPE_BOX || tileNext == TILE_TYPE_RED_BOX)
	{
		int tempTilyNext = rmap.GetTileType(moveX + player.delX + 32, moveY + player.delY + 32);
		if (tempTilyNext == TILE_TYPE_NONE || tempTilyNext == TILE_TYPE_FINISHPOINT)
		{
			player.flagMove = true;
			CSurface::onDraw(ren, texture_clear_none, player.X, player.Y, 64);
			if (rmap.GetTileType(player.X + 32, player.Y + 32) == 3) CSurface::onDraw(ren, texture_clear_finish, player.X, player.Y, 64);
			if (tileNext == TILE_TYPE_BOX)
			{
				CSurface::onDraw(ren, texture_clear_none, moveX, moveY, 64);
				rmap.TileList[rmap.GetTileID(moveX, moveY)].TileID = TILE_TYPE_NONE;
			}
			else
			{
				CSurface::onDraw(ren, texture_clear_finish, moveX, moveY, 64);
				rmap.TileList[rmap.GetTileID(moveX, moveY)].TileID = TILE_TYPE_FINISHPOINT;
				CLevel::kolPoint--;
			}
			if (tempTilyNext == TILE_TYPE_NONE)
			{
				CSurface::onDraw(ren, texture_clear_box, moveX + player.delX, moveY + player.delY, 64);
				rmap.TileList[rmap.GetTileID(moveX + player.delX, moveY + player.delY)].TileID = TILE_TYPE_BOX;
				//return ;
			}
			if (tempTilyNext == TILE_TYPE_FINISHPOINT)
			{
				CSurface::onDraw(ren, texture_clear_redBox, moveX + player.delX, moveY + player.delY, 64);
				rmap.TileList[rmap.GetTileID(moveX + player.delX, moveY + player.delY)].TileID = TILE_TYPE_RED_BOX;
				CLevel::kolPoint++;
				//return ;
			}
			rmap.vectorShow();
			return;
		}
	}
	player.flagMove = 0;
	return;
}

void SceneManager::offPull(SDL_Renderer* ren)
{
	float moveX = player.delX + player.X, moveY = player.delY + player.Y;
	int tileNext = rmap.GetTileType(moveX + 32, moveY + 32);
	//if (tileNext == 0 || tileNext == 3)
	if (tileNext == TILE_TYPE_NONE || tileNext == TILE_TYPE_FINISHPOINT)
	{
		player.flagMove = 1;
		CSurface::onDraw(ren, texture_clear_none, player.X, player.Y, 64);
		if (rmap.GetTileType(player.X + 32, player.Y + 32) == TILE_TYPE_FINISHPOINT) CSurface::onDraw(ren, texture_clear_finish, player.X, player.Y, 64);
		return;
	}
	//if (tileNext == 2 || tileNext == 4)
	if (tileNext == TILE_TYPE_BOX || tileNext == TILE_TYPE_RED_BOX)
	{
		int tempTily = rmap.GetTileType(moveX + player.delX + 32, moveY + player.delY + 32);
		if (tempTily == TILE_TYPE_NONE || tempTily == TILE_TYPE_FINISHPOINT)
		{

			player.flagMove = 1;
			CSurface::onDraw(ren, texture_clear_none, player.X, player.Y, 64);
			if (rmap.GetTileType(player.X + 32, player.Y + 32) == 3) CSurface::onDraw(ren, texture_clear_finish, player.X, player.Y, 64);
			if (tileNext == TILE_TYPE_BOX)
			{
				CSurface::onDraw(ren, texture_clear_none, moveX, moveY, 64);
				rmap.TileList[rmap.GetTileID(moveX, moveY)].TileID = 0;
			}
			else
			{
				CSurface::onDraw(ren, texture_clear_finish, moveX, moveY, 64);
				rmap.TileList[rmap.GetTileID(moveX, moveY)].TileID = 3;
				CLevel::kolPoint--;
			}
			if (tempTily == TILE_TYPE_NONE)
			{
				CSurface::onDraw(ren, texture_clear_box, moveX + player.delX, moveY + player.delY, 64);
				rmap.TileList[rmap.GetTileID(moveX + player.delX, moveY + player.delY)].TileID = 2;
				//return ;
			}
			if (tempTily == TILE_TYPE_FINISHPOINT)
			{
				CSurface::onDraw(ren, texture_clear_redBox, moveX + player.delX, moveY + player.delY, 64);
				rmap.TileList[rmap.GetTileID(moveX + player.delX, moveY + player.delY)].TileID = 4;
				CLevel::kolPoint++;
				//return ;
			}
			rmap.vectorShow();
			return;

		}
	}
	player.flagMove = 0;
}

void SceneManager::casheTextureClear(SDL_Renderer* ren)
{
	texture_clear_none = CSurface::onLoad("texture/none.bmp", ren);
	texture_clear_redBox = CSurface::onLoad("texture/redBox.bmp", ren);
	texture_clear_finish = CSurface::onLoad("texture/finishPoint.bmp", ren);
	texture_clear_box = CSurface::onLoad("texture/box.bmp", ren);

	texture_end_game = CSurface::onLoad("texture/menu/endGame.bmp", ren);
	texture_pull_on = CSurface::onLoad("texture/menu/pullOn.bmp", ren);
	texture_pull_off = CSurface::onLoad("texture/menu/pullOf.bmp", ren);
	texture_help_one = CSurface::onLoad("texture/menu/helpOne.bmp", ren);
	texture_help_two = CSurface::onLoad("texture/menu/helpTwo.bmp", ren);
}

bool SceneManager::isEnd()
{
	if (CLevel::kolPoint == CLevel::maxPoint)
	{
		CLevel::kolPoint = 0;
		CLevel::currentLevel++;
		//cout << endl << CLevel::currentLevel << endl;
		return true;
	}
	return false;
}

void SceneManager::reset(SDL_Renderer* ren)
{
	if (CLevel::currentLevel > CLevel::maxLevel)
	{
		rmap.clear(ren);
		rmap.TileList.clear();
		SDL_RenderClear(ren);
		SDL_RenderPresent(ren);
		exitGame(ren);
		return;
	}
	else {
		rmap.TileList.clear();
		SDL_RenderClear(ren);
		CLevel::kolPoint = 0;
		lvl.casheLevel();
		player.X = CLevel::XPlayer;
		player.Y = CLevel::YPlayer;
	}
}

void SceneManager::changeLevelToNext(SDL_Renderer* ren)
{
	string strLevel = lvl.strLVL;
	rmap.acceptWH();
	rmap.OnLoad(lvl.strLVL.c_str());
	rmap.OnRender(ren, 50, 50);
	player.onRender(ren);
	CSurface::onDraw(ren, texture_pull_off, 10, CLevel::height * 64, 750, 50);
	CSurface::onDraw(ren, texture_help_one, 10, CLevel::height * 64 + 60, 560, 30);
	CSurface::onDraw(ren, texture_help_two, 10, CLevel::height * 64 + 95, 310, 30);
}

void SceneManager::exitGame(SDL_Renderer* ren)
{
	//render();
	CSurface::onDraw(ren, texture_clear_none, 0, 0, 820, 820);
	CSurface::onDraw(ren, texture_end_game, 270, 410, 280, 52);
	SDL_RenderPresent(ren);
	this_thread::sleep_for(std::chrono::seconds(5));
	run = false;
}

