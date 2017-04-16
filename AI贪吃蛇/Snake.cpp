#include "stdafx.h"
#include "Snake.h"


Snake::Snake()
{
	pHead = new POSITION;
	pHead->corX = 1;
	pHead->corY = 1;
	pHead->pNext = NULL;

	posLast.corX = pHead->corX;
	posLast.corY = pHead->corY;

	direction = 'R';

	for (int i = 0; i < 2; i++)
	{
		move();
		increase();
	}

	headImg = ege::newimage(BLOCK_SIZE, BLOCK_SIZE);
	bodyImg = ege::newimage(BLOCK_SIZE, BLOCK_SIZE);
	ege::getimage(headImg, "../DATA/head.bmp", BLOCK_SIZE, BLOCK_SIZE);
	ege::getimage(bodyImg, "../DATA/body.bmp", BLOCK_SIZE, BLOCK_SIZE);
}


Snake::~Snake()
{
	while (pHead!= NULL)
	{
		POSITION *pTemp = pHead;
		pHead = pHead->pNext;
		delete pTemp;
	}

	ege::delimage(headImg);
	ege::delimage(bodyImg);
}

void Snake::increase()
{
	POSITION *pNew = new POSITION;
	POSITION *pTemp = pHead;
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
	}
	pNew->corX = posLast.corX;
	pNew->corY = posLast.corY;
	pNew->pNext = NULL;
	pTemp->pNext = pNew;
}

void Snake::move()
{
	switch (direction)
	{
	case 'U':
	{
		int XBefore = pHead->corX;
		int YBefore = pHead->corY;
		int XAfter = pHead->corX;
		int YAfter = pHead->corY;
		pHead->corY--;
		POSITION *pTemp = pHead->pNext;
		while (pTemp != NULL)
		{
			XAfter = pTemp->corX;
			YAfter = pTemp->corY;
			pTemp->corX = XBefore;
			pTemp->corY = YBefore;
			XBefore = XAfter;
			YBefore = YAfter;
			pTemp = pTemp->pNext;
		}
		posLast.corX = XAfter;
		posLast.corY = YAfter;
	}
		break;

	case 'D':
	{
		int XBefore = pHead->corX;
		int YBefore = pHead->corY;
		int XAfter = pHead->corX;
		int YAfter = pHead->corY;
		pHead->corY++;
		POSITION *pTemp = pHead->pNext;
		while (pTemp != NULL)
		{
			XAfter = pTemp->corX;
			YAfter = pTemp->corY;
			pTemp->corX = XBefore;
			pTemp->corY = YBefore;
			XBefore = XAfter;
			YBefore = YAfter;
			pTemp = pTemp->pNext;
		}
		posLast.corX = XAfter;
		posLast.corY = YAfter;
	}
		break;

	case 'L':
	{
		int XBefore = pHead->corX;
		int YBefore = pHead->corY;
		int XAfter = pHead->corX;
		int YAfter = pHead->corY;
		pHead->corX--;
		POSITION *pTemp = pHead->pNext;
		while (pTemp != NULL)
		{
			XAfter = pTemp->corX;
			YAfter = pTemp->corY;
			pTemp->corX = XBefore;
			pTemp->corY = YBefore;
			XBefore = XAfter;
			YBefore = YAfter;
			pTemp = pTemp->pNext;
		}
		posLast.corX = XAfter;
		posLast.corY = YAfter;
	}
		break;
		
	case 'R':
	{
		int XBefore = pHead->corX;
		int YBefore = pHead->corY;
		int XAfter = pHead->corX;
		int YAfter = pHead->corY;
		pHead->corX++;
		POSITION *pTemp = pHead->pNext;
		while (pTemp != NULL)
		{
			XAfter = pTemp->corX;
			YAfter = pTemp->corY;
			pTemp->corX = XBefore;
			pTemp->corY = YBefore;
			XBefore = XAfter;
			YBefore = YAfter;
			pTemp = pTemp->pNext;
		}
		posLast.corX = XAfter;
		posLast.corY = YAfter;
	}
		break;

	default:
		break;
	}
}

void Snake::reDraw()
{
	ege::putimage(pHead->corX*BLOCK_SIZE, pHead->corY*BLOCK_SIZE, headImg, SRCCOPY);
	POSITION *pTemp = pHead;
	while (pTemp->pNext != NULL)
	{
		pTemp = pTemp->pNext;
		ege::putimage(pTemp->corX*BLOCK_SIZE, pTemp->corY*BLOCK_SIZE, bodyImg, SRCCOPY);
	}
}

bool Snake::isTochBody()
{
	POSITION *pTemp = pHead->pNext;
	while (pTemp != NULL)
	{
		if (pHead->corX == pTemp->corX && pHead->corY == pTemp->corY)
		{
			return true;
		}
		pTemp = pTemp->pNext;
	}
	return false;
}

bool Snake::isTouchBlock()
{
	if (pHead->corX == 0 || pHead->corX == COL - 1 || pHead->corY == 0 || pHead->corY == ROW - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

POSITION* Snake::getSnakePostion() const
{
	return pHead;
}

char Snake::getSnakeDirection() const
{
	return direction;
}

void Snake::setSnakeDirection(char direction)
{
	this->direction = direction;
}