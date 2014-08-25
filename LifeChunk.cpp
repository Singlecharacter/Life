#include "LifeChunk.h"

LifeChunk::LifeChunk() : x(0), y(0)
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            cellArray[i][j] = false;
        }
    }
}

LifeChunk::LifeChunk(int startX, int startY) : x(startX), y(startY)
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            cellArray[i][j] = false;
        }
    }
}

LifeChunk::~LifeChunk()
{

}

int LifeChunk::getX()
{
    return x;
}

void LifeChunk::setX(int newX)
{
    x = newX;
}

int LifeChunk::getY()
{
    return y;
}

void LifeChunk::setY(int newY)
{
    y = newY;
}

bool LifeChunk::getCellState(int cellY, int cellX)
{
    return cellArray[cellY][cellX];
}

void LifeChunk::setCellState(int cellY, int cellX, bool newState)
{
    cellArray[cellY][cellX] = newState;
}

int LifeChunk::getLiveCells()
{
    int liveCount = 0;
    for(int i = 0;i<16;i++)
    {
        for(int j = 0;j<16;j++)
        {
            if(cellArray[i][j] == 1)
            {
                liveCount++;
            }
        }
    }
    return liveCount;
}
