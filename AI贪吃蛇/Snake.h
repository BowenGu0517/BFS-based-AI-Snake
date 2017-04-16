#pragma once

class Snake
{
private:
	ege::PIMAGE headImg;
	ege::PIMAGE bodyImg;
	POSITION *pHead;
	POSITION posLast;
	char direction;

public:
	Snake();
	~Snake();
	void move();
	void reDraw();
	void increase();
	bool isTochBody();
	bool isTouchBlock();
	POSITION* getSnakePostion() const;
	char getSnakeDirection() const;
	void setSnakeDirection(char direction);
};

