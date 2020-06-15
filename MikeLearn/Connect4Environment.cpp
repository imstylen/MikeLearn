#include "Connect4Environment.h"

Connect4Environment::Connect4Environment(int xDim, int yDim)
{
	this->xDim = xDim;
	this->yDim = yDim;


	for (int i = 0; i < yDim; i++)
	{
		std::vector<float> row;
		for (int j = 0; j < xDim; j++)
		{
			row.push_back(0.f);
		}
		board.push_back(row);
	}
	printBoard();
	loop();
}

void Connect4Environment::loop()
{
	while (gameOver == false)
	{
		//Player 1 move
		int p1Move;
		std::cin >> p1Move;
		move(-1.f, p1Move);

		if (gameOver) { break; }

		//Player 2 move
		int p2Move;
		std::cin >> p2Move;
		move(1.f, p2Move);

	}


}

void Connect4Environment::move(float player, int column)
{
	for (int i = 0; i < yDim; i++)
	{
		if (board[i][column] == 0.f)
		{
			board[i][column] = player;
			printBoard();
			bool over = checkGameOver(player, column,i);
			if (over)
			{
				std::cout << "Game Over!" << std::endl;
				gameOver = true;
			}
			break;
		}

	}
}

void Connect4Environment::printBoard()
{
	std::cout << std::string(100, '\n');
	std::cout << "0 1 2 3 4 5 6" << std::endl;
	std::cout << "-------------" << std::endl;

	for (int y = yDim - 1; y >= 0; y--)
	{
		for (float x : board[y])
		{
			if (x == -1)
			{
				std::cout << "X" << ' ';
			}
			else if (x == 1)
			{
				std::cout << "0" << ' ';
			}
			else
			{
				std::cout << "-" << ' ';
			}
		}
		std::cout << std::endl;
	}
	std::cout << "-------------" << std::endl;

	
}

bool Connect4Environment::checkGameOver(float player, int x, int y)
{

	//north south
	if ((shootRay(player, x, y, 0, 1) + shootRay(player, x, y, 0, -1)) >= 3)
	{
		return true;
	}

	//east west
	if ((shootRay(player, x, y, 1, 0) + shootRay(player, x, y, -1,0)) >= 3)
	{
		return true;
	}

	//north-east south-west
	if ((shootRay(player, x, y, 1, 1) + shootRay(player, x, y, -1, -1)) >= 3)
	{
		return true;
	}

	//north-east south-west
	if ((shootRay(player, x, y, -1, 1) + shootRay(player, x, y, 1, -1)) >= 3)
	{
		return true;
	}

	return false;

}

int Connect4Environment::shootRay(float player, int x, int y, int xDir, int yDir)
{
	int xi = x;
	int yi = y;
	int count;

	bool keepChecking = true;
	count = 0;

	while (keepChecking)
	{
		xi = xi + xDir;
		yi = yi + yDir;

		if (xi < 0 || xi >= xDim || yi < 0 || yi >= yDim)
		{
			keepChecking = false;
			break;
		}
		if (board[yi][xi] == player)
		{
			count = count + 1;
		}
		else
		{
			keepChecking = false;
		}

	}
	return count;
}
