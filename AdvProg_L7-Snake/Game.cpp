// UPDATE THIS FILE
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "Game.h"

using namespace std;
Game::Game(int _width, int _height)
:width(_width), height(_height),						  // play screen
	  squares(_height, vector<CellType>(_width, CELL_EMPTY)),snake(*this, Position(_width / 2, _height / 2)),		  // init snake positin in middle of play screen
	  currentDirection(Direction::RIGHT),
	  status(GAME_RUNNING),
	  score(0)
	  {
	// add new cheery in game initiation
	addCherry();
}

Game::~Game()
{// dtor
}
void Game::snakeMoveTo(Position pos)
{
	switch (getCellType(pos))
	{
	case CELL_SNAKE:
	case CELL_OFF_BOARD:
		status = GAME_OVER;
		break;
	case CELL_CHERRY:
		++score;
		snake.eatCherry();
		addCherry();
		break;
	default:
		snake.slideTo(pos);
		break;
	}
}
void Game::snakeLeave(Position position)
{
	// Suggestion: use setCellType() method in Game class
	// START CODE HERE
	//  
	//
	//
	// END CODE HERE
	setCellType(position, CELL_EMPTY);
}
void Game::processUserInput(Direction direction)
{
	inputQueue.push(direction);
}
bool Game::canChange(Direction current, Direction next) const
{
	if ((current == UP || current == DOWN) && (next == UP || next == DOWN))
		return 0;
	if ((current == LEFT || current == RIGHT) && (next == LEFT || next == RIGHT))
		return 0;
	return 1;
}

void Game::nextStep()
{
	while (!inputQueue.empty())
	{ Direction next;
		next = inputQueue.front();
		inputQueue.pop();
		if (canChange(currentDirection, next))
		{
			currentDirection = next;
			break;
		}
    }
	snake.move(currentDirection);
}
void Game::addCherry()
{
	do
	{
		Position randomPos;
		randomPos = Position(rand() % width, rand() % height);
		if (getCellType(randomPos) == CELL_EMPTY)
		{
			cherryPosition = randomPos;
			setCellType(randomPos, CELL_CHERRY);
			break;
		}
	} while (true);
}
void Game::setCellType(Position pos, CellType cellType)
{
	// if position is inside the play screen (width, height), set to the cellType.
	// Otherwise, do nothing
	// Suggestion: use pos.isInsideBox(...) in Position class
	//
	// START CODE HERE
	//  
	// END CODE HERE
	if (pos.isInsideBox(0, 0, width, height))
	{
		squares[pos.y][pos.x] = cellType;
	}
}
CellType Game::getCellType(Position pos) const
{
	return pos.isInsideBox(0, 0, width, height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}
// DO NOT change this method
vector<Position> Game::getSnakePositions() const
{
	return snake.getPositions();
}
GameStatus Game::getGameStatus()
{
	return status;
}
int Game::getWidth()
{
	return width;
}
int Game::getHeight()
{
	return height;
}
Snake Game::getSnake()
{
	return snake;
}