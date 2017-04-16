                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             #include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	pMapArr = new int*[ROW];
	for (int r = 0; r < ROW; r++)
	{
		pMapArr[r] = new int[COL];
	}
	initMap();

	blockImg = ege::newimage(BLOCK_SIZE, BLOCK_SIZE);
	floorImg = ege::newimage(BLOCK_SIZE, BLOCK_SIZE);
	ege::getimage(blockImg, "../DATA/block.bmp", BLOCK_SIZE, BLOCK_SIZE);
	ege::getimage(floorImg, "../DATA/floor.bmp", BLOCK_SIZE, BLOCK_SIZE);
}


BackGround::~BackGround()
{
	delete[] pMapArr;
	pMapArr = NULL;
	ege::delimage(blockImg);
	ege::delimage(floorImg);
}

void BackGround::initMap()
{
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (r == 0 || r == ROW - 1 || c == 0 || c == COL - 1)
			{
				pMapArr[r][c] = 1;
			}
			else
			{
				pMapArr[r][c] = 0;
			}
		}
	}
}

void BackGround::reDraw()
{
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			switch (pMapArr[r][c])
			{
			case 0:
				ege::putimage(c*BLOCK_SIZE, r*BLOCK_SIZE, floorImg, SRCCOPY);
				break;
			case 1:
				ege::putimage(c*BLOCK_SIZE, r*BLOCK_SIZE, blockImg, SRCCOPY);
				break;
			default:
				break;
			}
		}
	}
}
