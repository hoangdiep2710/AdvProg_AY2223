#include "Snake.h"
#include "Game.h"
#include <iostream>
Snake::Snake(Game &_game, Position start)
    : head(new SnakeNode(start)), tail(head), game(_game), cherry(0)
{
       game.snakeMoveTo(start);
}

// set some attributes as default value
// PLEASE UPDATE THIS METHOD
Snake::~Snake()
{
    for (SnakeNode *p = tail; p != nullptr;)
    {
        SnakeNode *nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

// DO NOT CHANGE METHOD
vector<Position> Snake::getPositions() const
{
    vector<Position> res;
    for (SnakeNode *p = tail; p != nullptr; p = p->next)
        res.push_back(p->position);
    return res;
}
void Snake::growAtFront(Position newPosition)
{head->next = new SnakeNode(newPosition, nullptr);
    head = head->next;
}
void Snake::slideTo(Position newPosition)
{
    if (tail->next == nullptr)
    {
         tail->position = newPosition;
    }
    else
    {
        SnakeNode *oldTailNode = tail;
        // cut the old tail off the snake
        tail = tail->next;
        oldTailNode->next = nullptr;

        // move it to the head of the snake
        oldTailNode->position = newPosition;
        head->next = oldTailNode;
        head = oldTailNode;
    }
}
void Snake::eatCherry()
{
    ++cherry;
}
void Snake::move(Direction direction)
{
    Position newPosition = head->position.move(direction);

    /* YOUR CODE HERE */

    // If gameOver, return ; 
    /* YOUR CODE HERE */
    game.snakeMoveTo(newPosition);

    // If gameOver, return ;
    if (game.isGameOver())
        return;
if (cherry > 0)
    {
        --cherry;
        growAtFront(newPosition);
    }
    else
    {
        game.snakeLeave(tail->position);
        slideTo(newPosition);
    }
}
int Snake::getNumCherry()
{
    return cherry;
}
SnakeNode *Snake::getHead()
{
    return head;
}
SnakeNode *Snake::getTail()
{
    return tail;
}
