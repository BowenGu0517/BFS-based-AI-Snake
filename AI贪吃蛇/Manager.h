#pragma once
#include "BackGround.h"
#include "Snake.h"
#include "Food.h"

class Manager
{
	static const int timeInterval;
private:
	BackGround *background;
	Snake *snake;
	Food *food;
	bool isFoodInvalid(Food *food, Snake *snake);
	bool isGetFood(Food *food, Snake *snake);
	
	BFSPOSITION **pBFSArr;
	int directionArr[4][2];
	void BFSSearch(Food *food, Snake *snake);

public:
	Manager();
	~Manager();
	void run();
};

