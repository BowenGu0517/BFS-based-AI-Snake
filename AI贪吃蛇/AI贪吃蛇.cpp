// AIÃ∞≥‘…ﬂ.cpp : Defines the entry point for the console application.
/**************************************************************
*				   Project Name:AI Snake	                  *
*					Developer: Bowen Gu						  *
*			  External library: ege graphic lib				  *
*					Platform: VS2015  C++					  *
*		Algorithm: Breadth First Search (BFS) algorithm		  *
*						Version: 1.0						  *
*	Todo: Fix the problem that the snake always go straight   *
*	      when the snake head is sorround by the loop         *
**************************************************************/

#include "stdafx.h"
#include "Manager.h"

int main()
{
	srand((unsigned)time(NULL));
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	Manager myGame1;
	myGame1.run();

	getchar();
	closegraph();

    return 0;
}

