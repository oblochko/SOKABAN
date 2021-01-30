#pragma once

#ifndef _CLEVEL_H_
#define _CLEVEL_H_

#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include <SDL.h>

#include "CSurface.h"

using namespace std;

class CLevel
{
public:
	void casheLevel();
public:
	CLevel();
	static int kolPoint;
	static int currentLevel;
	static int maxLevel;
	static int maxPoint;
	static int XPlayer;
	static int YPlayer;
	static int width;
	static int height;
public:
	string strLVL;
};

#endif

