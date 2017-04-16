#pragma once

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

#define BLOCK_SIZE (20)

#define COL (WINDOW_WIDTH/BLOCK_SIZE)
#define ROW (WINDOW_HEIGHT/BLOCK_SIZE)

#define VERTEX_EXPLORED (1)
#define VERTEX_UNEXPLORED (-1)

struct POSITION
{
	int corX;
	int corY;
	struct POSITION* pNext;
	bool operator==(POSITION const&pos)
	{
		return (pos.corX == this->corX && pos.corY == this->corY);
	}
};

struct BFSPOSITION
{
	POSITION position;
	BFSPOSITION* pPrevPos;
	int isVertexExplored;
};
