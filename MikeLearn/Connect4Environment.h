#pragma once
#include "Agent.h"
#include <vector>
#include <string>
#include <iostream>
class Connect4Environment
{

private:
	std::vector<Agent*> agents;
	std::vector<std::vector<float>> board;
	int xDim;
	int yDim;
	bool gameOver = false;
protected:

public:
	Connect4Environment(int xDim, int yDim, std::vector<Agent*> agents);
	void loop();
	void move(float player, int column);
	void printBoard();
	bool checkGameOver(float player, int x, int y);
	int shootRay(float player, int x, int y, int xDir, int yDir);
};

