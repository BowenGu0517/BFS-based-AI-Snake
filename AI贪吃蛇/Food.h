#pragma once

class Food
{
private:
	POSITION foodPos;
	ege::PIMAGE foodImg;

public:
	Food();
	~Food();
	void reDraw();
	POSITION getFoodPostion();
};

