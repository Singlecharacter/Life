#ifndef LIFECHUNK_H
#define LIFECHUNK_H

//LifeChunk contains a 16x16 boolean array that represents a 16x16 grid of life cells

class LifeChunk
{

public:

    LifeChunk();
    LifeChunk(int startX, int startY);
    ~LifeChunk();

    int getX();
    void setX(int newX);
    int getY();
    void setY(int newY);

    bool getCellState(int cellX, int cellY);
    void setCellState(int cellX, int cellY, bool newState);

    int getLiveCells();

private:

    bool cellArray[16][16];
    int x, y;
};

#endif // LIFECHUNK_H
