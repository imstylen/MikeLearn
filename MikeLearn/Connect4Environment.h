#pragma once
#include <vector>
#include <string>
#include <iostream>
class Connect4Environment
{

private:

	std::vector<std::vector<float>> board;
	int xDim;
	int yDim;
	bool gameOver = false;
protected:

public:
	Connect4Environment(int xDim, int yDim);
	void loop();
	void move(float player, int column);
	void printBoard();
	bool checkGameOver(float player, int x, int y);
	int shootRay(float player, int x, int y, int xDir, int yDir);
};

