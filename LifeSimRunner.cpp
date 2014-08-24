#include "LifeSimRunner.h"

LifeSimRunner::LifeSimRunner(std::string fname = "")
{
    chunkList.resize(0);
    randomize();
}

LifeSimRunner::~LifeSimRunner()
{

    chunkList.resize(0);
}

void LifeSimRunner::simGeneration()
{
    std::vector<LifeChunk> nextGenChunkList = chunkList;
    //Loop through each chunk, performing cell state change checks
    for(int i = 0;i < chunkList.size();i++)
    {
        LifeChunk *currentChunk = &chunkList.at(i);
        //Check inner square of cells
        for(int j = 1;j < 15;j++)
        {
            for(int k = 1;k < 15;k++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(j-1,k-1))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j-1,k))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j-1,k+1))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j+1,k-1))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j+1,k))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j+1,k+1))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j,k-1))
                {
                    liveNeighbors += 1;
                }
                else if(currentChunk->getCellState(j,k+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(j,k,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(j,k,true);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(j,k,false);
                }
            }
        }

        //Check to see if surrounding chunks exist for edge checking
        LifeChunk *leftChunk = NULL;
        LifeChunk *rightChunk = NULL;
        LifeChunk *topChunk = NULL;
        LifeChunk *bottomChunk = NULL;
        LifeChunk *topLeftChunk = NULL;
        LifeChunk *topRightChunk = NULL;
        LifeChunk *bottomLeftChunk = NULL;
        LifeChunk *bottomRightChunk = NULL;

        for(int j = 0;j < chunkList.size();j++)
        {
            if(chunkList.at(j).getX() == currentChunk->getX())
            {
                if(chunkList.at(j).getY() == currentChunk->getY() - 1)
                {
                    topChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk->getY() + 1)
                {
                    bottomChunk = &chunkList.at(j);
                }
            }
            else if(chunkList.at(j).getX() == currentChunk->getX()-1)
            {
                if(chunkList.at(j).getY() == currentChunk->getY() - 1)
                {
                    topLeftChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk->getY() + 1)
                {
                    bottomLeftChunk = &chunkList.at(j);
                }
            }
            else if(chunkList.at(j).getX() == currentChunk->getX()+1)
            {
                if(chunkList.at(j).getY() == currentChunk->getY() - 1)
                {
                    topRightChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk->getY() + 1)
                {
                    bottomRightChunk = &chunkList.at(j);
                }
            }

            if(chunkList.at(j).getY() == currentChunk->getY())
            {
                if(chunkList.at(j).getX() == currentChunk->getX() - 1)
                {
                    leftChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getX() == currentChunk->getX() + 1)
                {
                    rightChunk = &chunkList.at(j);
                }
            }
        }

        //Check top row of cells
        if(topChunk == NULL)
        {
            for(int j = 1; j < 15; j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j-1,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(j,0,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(j,0,true);
                    LifeChunk temp(currentChunk->getX(),currentChunk->getY()-1);
                    nextGenChunkList.push_back(temp);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(j,0,false);
                }
            }
        }
        else
        {
            for(int j = 1; j < 15; j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j-1,1))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j,1))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(j,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,1))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(j,0,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(j,0,true);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(j,0,false);
                }
            }
        }

        //Check bottom row of cells
        if(bottomChunk == NULL)
        {
            for(int j = 1; j < 15; j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j-1,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,14))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(j,15,false);
                }
                if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(j,15,true);
                    LifeChunk temp(currentChunk->getX(),currentChunk->getY()+1);
                    nextGenChunkList.push_back(temp);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(j,15,false);
                }
            }
        }
        else
        {
            for(int j = 1; j < 15; j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j-1,14))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j,14))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(j,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(j+1,14))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(j,15,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(j,15,true);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(j,15,false);
                }
            }
        }

        //Check left row of cells
        if(leftChunk == NULL)
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(0,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(0,j,true);
                    LifeChunk temp(currentChunk->getX()-1,currentChunk->getY());
                    nextGenChunkList.push_back(temp);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(0,j,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(1,j+1))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(15,j))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(0,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(0,j,true);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(0,j,false);
                }
            }
        }

        //Check right row of cells
        if(rightChunk == NULL)
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(15,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(15,j,true);
                    LifeChunk temp(currentChunk->getX()+1,currentChunk->getY());
                    nextGenChunkList.push_back(temp);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(15,j,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk->getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk->getCellState(14,j+1))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(0,j))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    nextGenChunkList.at(i).setCellState(15,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    nextGenChunkList.at(i).setCellState(15,j,true);
                }
                else if(liveNeighbors > 3)
                {
                    nextGenChunkList.at(i).setCellState(15,j,false);
                }
            }
        }

        //Check top left corner
        int liveNeighbors = 0;
        if(currentChunk->getCellState(0,1))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(1,0))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(1,1))
        {
            liveNeighbors += 1;
        }

        if(topChunk != NULL)
        {
            if(topChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
            if(topChunk->getCellState(1,15))
            {
                liveNeighbors += 1;
            }
        }

        if(leftChunk != NULL)
        {
            if(leftChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
            if(leftChunk->getCellState(15,1))
            {
                liveNeighbors += 1;
            }
        }

        if(topLeftChunk != NULL)
        {
            if(topLeftChunk->getCellState(15,15))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }
        else if(liveNeighbors == 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,true);
            if(topChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX(),currentChunk->getY()-1);
                nextGenChunkList.push_back(temp);
            }
            if(leftChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()-1,currentChunk->getY());
                nextGenChunkList.push_back(temp);
            }
            if(topLeftChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()-1,currentChunk->getY()-1);
                nextGenChunkList.push_back(temp);
            }
        }
        else if(liveNeighbors > 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }

        //Check top right corner
        liveNeighbors = 0;
        if(currentChunk->getCellState(15,1))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(14,0))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(14,1))
        {
            liveNeighbors += 1;
        }

        if(topChunk != NULL)
        {
            if(topChunk->getCellState(15,15))
            {
                liveNeighbors += 1;
            }
            if(topChunk->getCellState(14,15))
            {
                liveNeighbors += 1;
            }
        }

        if(rightChunk != NULL)
        {
            if(rightChunk->getCellState(0,0))
            {
                liveNeighbors += 1;
            }
            if(rightChunk->getCellState(0,1))
            {
                liveNeighbors += 1;
            }
        }

        if(topRightChunk != NULL)
        {
            if(topLeftChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }
        else if(liveNeighbors == 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,true);
            if(topChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX(),currentChunk->getY()-1);
                nextGenChunkList.push_back(temp);
            }
            if(rightChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()+1,currentChunk->getY());
                nextGenChunkList.push_back(temp);
            }
            if(topRightChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()+1,currentChunk->getY()-1);
                nextGenChunkList.push_back(temp);
            }
        }
        else if(liveNeighbors > 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }

        //Check bottom right corner
        liveNeighbors = 0;
        if(currentChunk->getCellState(15,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(14,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(14,15))
        {
            liveNeighbors += 1;
        }

        if(bottomChunk != NULL)
        {
            if(bottomChunk->getCellState(14,0))
            {
                liveNeighbors += 1;
            }
            if(bottomChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
        }

        if(rightChunk != NULL)
        {
            if(rightChunk->getCellState(0,14))
            {
                liveNeighbors += 1;
            }
            if(rightChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
        }

        if(bottomRightChunk != NULL)
        {
            if(bottomRightChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }
        else if(liveNeighbors == 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,true);
            if(bottomChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX(),currentChunk->getY()+1);
                nextGenChunkList.push_back(temp);
            }
            if(rightChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()+1,currentChunk->getY());
                nextGenChunkList.push_back(temp);
            }
            if(bottomRightChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()+1,currentChunk->getY()+1);
                nextGenChunkList.push_back(temp);
            }
        }
        else if(liveNeighbors > 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }

        //Check bottom left corner
        liveNeighbors = 0;
        if(currentChunk->getCellState(0,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(1,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk->getCellState(1,15))
        {
            liveNeighbors += 1;
        }

        if(bottomChunk != NULL)
        {
            if(bottomChunk->getCellState(0,0))
            {
                liveNeighbors += 1;
            }
            if(bottomChunk->getCellState(0,1))
            {
                liveNeighbors += 1;
            }
        }

        if(leftChunk != NULL)
        {
            if(leftChunk->getCellState(15,14))
            {
                liveNeighbors += 1;
            }
            if(leftChunk->getCellState(15,15))
            {
                liveNeighbors += 1;
            }
        }

        if(bottomLeftChunk != NULL)
        {
            if(bottomRightChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }
        else if(liveNeighbors == 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,true);
            if(bottomChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX(),currentChunk->getY()+1);
                nextGenChunkList.push_back(temp);
            }
            if(leftChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()-1,currentChunk->getY());
                nextGenChunkList.push_back(temp);
            }
            if(bottomLeftChunk == NULL)
            {
                LifeChunk temp(currentChunk->getX()-1,currentChunk->getY()+1);
                nextGenChunkList.push_back(temp);
            }
        }
        else if(liveNeighbors > 3)
        {
            nextGenChunkList.at(i).setCellState(0,0,false);
        }
    }

    chunkList.resize(0);
    chunkList = nextGenChunkList;
    nextGenChunkList.resize(0);
}

void LifeSimRunner::randomize()
{
    LifeChunk temp;
    chunkList.push_back(temp);
    temp.setX(1);
    chunkList.push_back(temp);
    temp.setX(2);
    chunkList.push_back(temp);
    temp.setY(1);
    chunkList.push_back(temp);
    temp.setX(1);
    chunkList.push_back(temp);
    temp.setX(0);
    chunkList.push_back(temp);

    for(int i = 0;i < chunkList.size();i++)
    {
        for(int j = 0;j < 16;j++)
        {
            for(int k = 0;k < 16;k++)
            {
                if(rand() % 2 == 1)
                {
                    chunkList.at(i).setCellState(j,k,true);
                }
            }
        }
    }
}