#include "stdafx.h"
#include "Food.h"


Food::Food()
{
	foodPos.corX = rand() % (COL - 2) + 1;
	foodPos.corY = rand() % (ROW - 2) + 1;
	foodImg = ege::newimage(BLOCK_SIZE, BLOCK_SIZE);
	ege::getimage(foodImg, "../DATA/food.bmp", BLOCK_SIZE, BLOCK_SIZE);
}

Food::~Food()
{
	ege::delimage(foodImg);
}

void Food::reDraw()
{
	ege::putimage(foodPos.corX*BLOCK_SIZE, foodPos.corY*BLOCK_SIZE, foodImg, SRCCOPY);
}

POSITION Food::getFoodPostion()
{
	POSITION tempPos;
	tempPos.corX = foodPos.corX;
	tempPos.corY = foodPos.corY;
	tempPos.pNext = NULL;
	return tempPos;
}