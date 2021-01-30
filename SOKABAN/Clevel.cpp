#include "CLevel.h"

int CLevel::currentLevel = 1;
int CLevel::kolPoint = 0;
int CLevel::height = 9;
int CLevel::width = 11;
int CLevel::maxPoint = 5;
int CLevel::maxLevel = 5;
int CLevel::XPlayer = 128;
int CLevel::YPlayer = 64;

CLevel::CLevel()
{
	strLVL = {};
}

void CLevel::casheLevel()
{
	switch (CLevel::currentLevel)
	{
	case 1:
	{
		cout << "1 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 11;
		CLevel::height = 9;
		CLevel::maxPoint = 5;
		CLevel::XPlayer = 128;
		CLevel::YPlayer = 64;
		strLVL = "map/level1.txt";
		break;
	}
	case 2:
	{
		cout << "2 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 9;
		CLevel::height = 5;
		CLevel::maxPoint = 3;
		CLevel::XPlayer = 128;
		CLevel::YPlayer = 64;
		strLVL = "map/level2.txt";
		break;
	}
	case 3:
	{
		cout << "3 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 9;
		CLevel::height = 9;
		CLevel::maxPoint = 3;
		CLevel::XPlayer = 192;
		CLevel::YPlayer = 320;
		strLVL = "map/level3.txt";
		break;
	}
	case 4:
	{
		cout << "4 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 9;
		CLevel::height = 7;
		CLevel::maxPoint = 5;
		CLevel::XPlayer = 64;
		CLevel::YPlayer = 192;
		strLVL = "map/level4.txt";
		break;
	}
	case 5:
	{
		cout << "5 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 7;
		CLevel::height = 8;
		CLevel::maxPoint = 4;
		CLevel::XPlayer = 128;
		CLevel::YPlayer = 64;
		strLVL = "map/level5.txt";
		break;
	}
	case 6:
	{
		cout << "6 level" << endl;
		CLevel::kolPoint = 0;
		CLevel::width = 7;
		CLevel::height = 8;
		CLevel::maxPoint = 4;
		CLevel::XPlayer = 128;
		CLevel::YPlayer = 64;
		strLVL = "map/level6.txt";
		break;
	}
	}
}

