#include "stdafx.h"
#include "Manager.h"

const int Manager::timeInterval =10;

Manager::Manager()
{
	background = new BackGround;
	snake = new Snake;
	food = new Food;
	while (isFoodInvalid(food, snake))
	{
		delete food;
		food = NULL;
		food = new Food;
	}

	pBFSArr = new BFSPOSITION*[ROW-2];
	for (int r = 0; r < ROW-2; r++)
	{
		pBFSArr[r] = new BFSPOSITION[COL-2];
	}

	for (int r = 0; r < ROW-2; r++)
	{
		for (int c = 0; c < COL-2; c++)
		{
			(pBFSArr[r] + c)->position.corX = c+1;
			(pBFSArr[r] + c)->position.corY = r+1;
			(pBFSArr[r] + c)->isVertexExplored = VERTEX_UNEXPLORED;
			(pBFSArr[r] + c)->pPrevPos = new BFSPOSITION;
			(pBFSArr[r] + c)->pPrevPos = NULL;
		}
	}

	directionArr[0][0] = 0;
	directionArr[0][1] = -1;

	directionArr[1][0] = 0;
	directionArr[1][1] = 1;

	directionArr[2][0] = -1;
	directionArr[2][1] = 0;

	directionArr[3][0] = 1;
	directionArr[3][1] = 0;
}


Manager::~Manager()
{
	if (background != NULL)
	{
		delete background;
	}
	if (snake != NULL)
	{
		delete snake;
	}
	if (food != NULL)
	{
		delete food;
	}
	delete pBFSArr;
}

bool Manager::isFoodInvalid(Food *food, Snake *snake)
{
	POSITION *pSnake = snake->getSnakePostion();
	while (pSnake != NULL)
	{
		if (food->getFoodPostion().corX == pSnake->corX && food->getFoodPostion().corY == pSnake->corY)
		{
			return true;
		}
		pSnake = pSnake->pNext;
	}
	return false;
}

bool Manager::isGetFood(Food *food, Snake *snake)
{
	return (snake->getSnakePostion()->corX == food->getFoodPostion().corX && snake->getSnakePostion()->corY == food->getFoodPostion().corY);
}

void Manager::run()
{
	while (true)
	{
		BFSSearch(food, snake);
		snake->move();
		if (isGetFood(food, snake))
		{
			snake->increase();
			
			delete food;
			food = NULL;
			food = new Food;
			while (isFoodInvalid(food, snake))
			{
				delete food;
				food = NULL;
				food = new Food;
			}
		}

		if (snake->isTouchBlock())
		{
			MessageBox(NULL, L"ײǽ��", L"ײǽ", MB_OK);

			delete snake;
			snake = NULL;
			snake = new Snake;

			delete food;
			food = NULL;
			food = new Food;
			while (isFoodInvalid(food, snake))
			{
				delete food;
				food = NULL;
				food = new Food;
			}

		}

		if (snake->isTochBody())
		{
			MessageBox(NULL, L"׷β��", L"׷β", MB_OK);

			delete snake;
			snake = NULL;
			snake = new Snake;

			delete food;
			food = NULL;
			food = new Food;
			while (isFoodInvalid(food, snake))
			{
				delete food;
				food = NULL;
				food = new Food;
			}
		}
		background->reDraw();
		snake->reDraw();
		food->reDraw();
		Sleep(timeInterval);
	}
}

void Manager::BFSSearch(Food *food, Snake *snake)
{
	for (int r = 0; r < ROW - 2; r++)
	{
		for (int c = 0; c < COL - 2; c++)
		{
			(pBFSArr[r] + c)->isVertexExplored = VERTEX_UNEXPLORED;
			(pBFSArr[r] + c)->pPrevPos = new BFSPOSITION;
			(pBFSArr[r] + c)->pPrevPos = NULL;
		}
	}


	BFSPOSITION *Vertex_Start = new BFSPOSITION;
	for (int r = 0; r < ROW - 2; r++)
	{
		for (int c = 0; c < COL - 2; c++)
		{
			if (*snake->getSnakePostion() == (pBFSArr[r] + c)->position)
			{
				Vertex_Start = pBFSArr[r] + c;
			}
		}
	}


	BFSPOSITION *Vertext_End = new BFSPOSITION;
	for (int r = 0; r < ROW - 2; r++)
	{
		for (int c = 0; c < COL - 2; c++)
		{
			if (food->getFoodPostion() == (pBFSArr[r] + c)->position)
			{
				Vertext_End = pBFSArr[r] + c;
			}
		}
	}
	
	std::queue<BFSPOSITION*> BFSVertexQueue;

	Vertex_Start->isVertexExplored = VERTEX_EXPLORED;
	BFSVertexQueue.push(Vertex_Start);
	bool hasAns = false;
	bool inerLoop = false;
	bool outterLoop = false;
	while (!BFSVertexQueue.empty())
	{
		int queueSize = BFSVertexQueue.size();
		for (int i = 0; i < queueSize ; i++)
		{
			BFSPOSITION* Vertex_temp = BFSVertexQueue.front();
			BFSVertexQueue.pop();


			if (Vertex_temp->position.corY > 1)
			{
				BFSPOSITION* Vertex_newTemp = new BFSPOSITION;
				Vertex_newTemp->position.corX = Vertex_temp->position.corX;
				Vertex_newTemp->position.corY = Vertex_temp->position.corY-1;

				bool isOk=true;

				POSITION *tempSnakeBody = snake->getSnakePostion();
				while (tempSnakeBody != NULL)
				{
					if (*tempSnakeBody == Vertex_newTemp->position)
					{
						isOk = false;
						break;
					}
					tempSnakeBody = tempSnakeBody->pNext;
				}
				if ((isOk)&&(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored == VERTEX_UNEXPLORED)
				{
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored = VERTEX_EXPLORED;
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->pPrevPos = Vertex_temp;
					BFSVertexQueue.push(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1));
				}
				if (Vertex_newTemp->position == Vertext_End->position)
				{
					inerLoop = true;
					break;
				}

			}
			

			if (Vertex_temp->position.corY <ROW-2)
			{
				BFSPOSITION* Vertex_newTemp = new BFSPOSITION;
				Vertex_newTemp->position.corX = Vertex_temp->position.corX;
				Vertex_newTemp->position.corY = Vertex_temp->position.corY +1;

				bool isOk = true;

				POSITION *tempSnakeBody = snake->getSnakePostion();
				while (tempSnakeBody != NULL)
				{
					if (*tempSnakeBody == Vertex_newTemp->position)
					{
						isOk = false;
						break;
					}
					tempSnakeBody = tempSnakeBody->pNext;
				}
				if ((isOk) && (pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored == VERTEX_UNEXPLORED)
				{
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored = VERTEX_EXPLORED;
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->pPrevPos = Vertex_temp;
					BFSVertexQueue.push(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1));
				}
				if (Vertex_newTemp->position == Vertext_End->position)
				{
					inerLoop = true;
					break;
				}
			}


			if (Vertex_temp->position.corX > 1)
			{
				BFSPOSITION* Vertex_newTemp = new BFSPOSITION;
				Vertex_newTemp->position.corX = Vertex_temp->position.corX-1;
				Vertex_newTemp->position.corY = Vertex_temp->position.corY;

				bool isOk = true;

				POSITION *tempSnakeBody = snake->getSnakePostion();
				while (tempSnakeBody != NULL)
				{
					if (*tempSnakeBody == Vertex_newTemp->position)
					{
						isOk = false;
						break;
					}
					tempSnakeBody = tempSnakeBody->pNext;
				}
				if ((isOk) && (pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored == VERTEX_UNEXPLORED)
				{
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored = VERTEX_EXPLORED;
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->pPrevPos = Vertex_temp;
					BFSVertexQueue.push(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1));
				}
				if (Vertex_newTemp->position == Vertext_End->position)
				{
					inerLoop = true;
					break;
				}
			}


			if (Vertex_temp->position.corY < COL-2)
			{
				BFSPOSITION* Vertex_newTemp = new BFSPOSITION;
				Vertex_newTemp->position.corX = Vertex_temp->position.corX+1;
				Vertex_newTemp->position.corY = Vertex_temp->position.corY;

				bool isOk = true;

				POSITION *tempSnakeBody = snake->getSnakePostion();
				while (tempSnakeBody != NULL)
				{
					if (*tempSnakeBody == Vertex_newTemp->position)
					{
						isOk = false;
						break;
					}
					tempSnakeBody = tempSnakeBody->pNext;
				}
				if ((isOk) && (pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored == VERTEX_UNEXPLORED)
				{
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->isVertexExplored = VERTEX_EXPLORED;
					(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1))->pPrevPos = Vertex_temp;
					BFSVertexQueue.push(pBFSArr[Vertex_newTemp->position.corY - 1] + (Vertex_newTemp->position.corX - 1));
				}
				if (Vertex_newTemp->position == Vertext_End->position)
				{
					inerLoop = true;
					break;
				}
			}
		}
		if (inerLoop)
		{
			outterLoop = true;
			break;
		}
	}
	if (outterLoop)
	{
		hasAns = true;
	}

	if (hasAns)
	{
		BFSPOSITION *pAnsPosition = BFSVertexQueue.back();
		while (pAnsPosition->pPrevPos != Vertex_Start)
		{
			pAnsPosition = pAnsPosition->pPrevPos;
		}

		POSITION prevPosition = *snake->getSnakePostion();
		POSITION newPostion = pAnsPosition->position;

		if (prevPosition.corX - newPostion.corX == 1)
		{
			this->snake->setSnakeDirection('L');
		}
		if (prevPosition.corX - newPostion.corX == -1)
		{
			this->snake->setSnakeDirection('R');
		}
		if (prevPosition.corY - newPostion.corY == 1)
		{
			this->snake->setSnakeDirection('U');
		}
		if (prevPosition.corY - newPostion.corY == -1)
		{
			this->snake->setSnakeDirection('D');
		}
	}
}