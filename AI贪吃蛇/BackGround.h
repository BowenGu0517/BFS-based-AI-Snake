#pragma once
#include "stdafx.h"


class BackGround
{
private:
	int** pMapArr;
	ege::PIMAGE blockImg;
	ege::PIMAGE floorImg;
	void initMap();

public:
	BackGround();
	~BackGround();
	void reDraw();
};
