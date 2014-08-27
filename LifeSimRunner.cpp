#include "LifeSimRunner.h"

LifeSimRunner::LifeSimRunner()
{
    chunkList.resize(0);
}

LifeSimRunner::~LifeSimRunner()
{

    chunkList.resize(0);
}

void LifeSimRunner::simGeneration()
{
    std::cout << "Starting generation simulation." << std::endl;
    std::vector<LifeChunk> nextGenChunkList = chunkList;
    //Loop through each chunk, performing cell state change checks
    for(int i = 0;i < chunkList.size();i++)
    {
        std::cout << "Checking chunk " << i+1 << " of " << chunkList.size() << "..." << std::endl;
        LifeChunk currentChunk = chunkList.at(i);
        LifeChunk currentNextGenChunk = nextGenChunkList.at(i);
        if(currentChunk.getLiveCells())
        {
            int liveInnerCells = 0;
            //Check inner square of cells
            for(int j = 1;j < 15;j++)
            {
                for(int k = 1;k < 15;k++)
                {
                    int liveNeighbors = 0;
                    if(currentChunk.getCellState(j-1,k-1))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j-1,k))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j-1,k+1))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j+1,k-1))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j+1,k))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j+1,k+1))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j,k-1))
                    {
                        liveNeighbors += 1;
                    }
                    if(currentChunk.getCellState(j,k+1))
                    {
                        liveNeighbors += 1;
                    }

                    if(liveNeighbors < 2)
                    {
                        currentNextGenChunk.setCellState(j,k,false);
                    }
                    else if(liveNeighbors == 2 && currentNextGenChunk.getCellState(j,k))
                    {
                        liveInnerCells += 1;
                    }
                    else if(liveNeighbors == 3)
                    {
                        currentNextGenChunk.setCellState(j,k,true);
                        liveInnerCells += 1;
                    }
                    else if(liveNeighbors > 3)
                    {
                        currentNextGenChunk.setCellState(j,k,false);
                    }
                }
            }
            std::cout << "Finished inner checking." << std::endl;
            std::cout << "Found " << liveInnerCells << " live cells." << std::endl;
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
            if(chunkList.at(j).getX() == currentChunk.getX())
            {
                if(chunkList.at(j).getY() == currentChunk.getY() - 1)
                {
                    topChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk.getY() + 1)
                {
                    bottomChunk = &chunkList.at(j);
                }
            }
            else if(chunkList.at(j).getX() == currentChunk.getX()-1)
            {
                if(chunkList.at(j).getY() == currentChunk.getY() - 1)
                {
                    topLeftChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk.getY() + 1)
                {
                    bottomLeftChunk = &chunkList.at(j);
                }
            }
            else if(chunkList.at(j).getX() == currentChunk.getX()+1)
            {
                if(chunkList.at(j).getY() == currentChunk.getY() - 1)
                {
                    topRightChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getY() == currentChunk.getY() + 1)
                {
                    bottomRightChunk = &chunkList.at(j);
                }
            }

            if(chunkList.at(j).getY() == currentChunk.getY())
            {
                if(chunkList.at(j).getX() == currentChunk.getX() - 1)
                {
                    leftChunk = &chunkList.at(j);
                }
                else if(chunkList.at(j).getX() == currentChunk.getX() + 1)
                {
                    rightChunk = &chunkList.at(j);
                }
            }
        }

        /////////////////////////
        //BEGIN EDGE ROW CHECKS//
        /////////////////////////

        std::cout << "Starting outer edge checking." << std::endl;
        //Check top row
        if(topChunk == NULL)
        {
            bool madeNewChunk = false;
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(0,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(0,j,true);
                    if(!madeNewChunk)
                    {
                        LifeChunk temp(currentChunk.getX(),currentChunk.getY()-1);
                        nextGenChunkList.push_back(temp);
                        madeNewChunk = true;
                    }
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(0,j,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(1,j+1))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(15,j))
                {
                    liveNeighbors += 1;
                }
                if(topChunk->getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(0,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(0,j,true);
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(0,j,false);
                }
            }
        }
        std::cout << "Finished top edge." << std::endl;

        //Check bottom row
        if(bottomChunk == NULL)
        {
            bool madeNewChunk = false;
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(15,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(15,j,true);
                    if(!madeNewChunk)
                    {
                        LifeChunk temp(currentChunk.getX(),currentChunk.getY()+1);
                        nextGenChunkList.push_back(temp);
                        madeNewChunk = true;
                    }
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(15,j,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(15,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(15,j+1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j-1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(14,j+1))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(0,j-1))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(0,j))
                {
                    liveNeighbors += 1;
                }
                if(bottomChunk->getCellState(0,j+1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(15,j,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(15,j,true);
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(15,j,false);
                }
            }
        }
        std::cout << "Finished bottom edge." << std::endl;

        //Check left row
        if(leftChunk == NULL)
        {
            bool madeNewChunk = false;
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j-1,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,1))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(j,0,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(j,0,true);
                    if(!madeNewChunk)
                    {
                        LifeChunk temp(currentChunk.getX()-1,currentChunk.getY());
                        nextGenChunkList.push_back(temp);
                        madeNewChunk = true;
                    }
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(j,0,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j-1,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j,1))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,1))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(j,15))
                {
                    liveNeighbors += 1;
                }
                if(leftChunk->getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(j,0,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(j,0,true);
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(j,0,false);
                }
            }
        }
        std::cout << "Finished left row." << std::endl;

        //Check right row
        if(rightChunk == NULL)
        {
            bool madeNewChunk = false;
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j-1,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,14))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(j,15,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(j,15,true);
                    if(!madeNewChunk)
                    {
                        LifeChunk temp(currentChunk.getX()+1,currentChunk.getY());
                        nextGenChunkList.push_back(temp);
                        madeNewChunk = true;
                    }
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(j,15,false);
                }
            }
        }
        else
        {
            for(int j = 1;j < 15;j++)
            {
                int liveNeighbors = 0;
                if(currentChunk.getCellState(j-1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,15))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j-1,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j,14))
                {
                    liveNeighbors += 1;
                }
                if(currentChunk.getCellState(j+1,14))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(j-1,0))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(j,0))
                {
                    liveNeighbors += 1;
                }
                if(rightChunk->getCellState(j+1,0))
                {
                    liveNeighbors += 1;
                }

                if(liveNeighbors < 2)
                {
                    currentNextGenChunk.setCellState(j,15,false);
                }
                else if(liveNeighbors == 3)
                {
                    currentNextGenChunk.setCellState(j,15,true);
                }
                else if(liveNeighbors > 3)
                {
                    currentNextGenChunk.setCellState(j,15,false);
                }
            }
        }
        std::cout << "Finished right row." << std::endl;

        ///////////////////////
        //END EDGE ROW CHECKS//
        ///////////////////////

        ///////////////////////
        //BEGIN CORNER CHECKS//
        ///////////////////////

        int liveNeighbors = 0;

        //Check top left corner
        liveNeighbors = 0;
        if(currentChunk.getCellState(0,1))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(1,0))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(1,1))
        {
            liveNeighbors += 1;
        }
        if(topChunk != NULL)
        {
            if(topChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
            if(topChunk->getCellState(15,1))
            {
                liveNeighbors += 1;
            }
        }
        if(leftChunk != NULL)
        {
            if(leftChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
            if(leftChunk->getCellState(1,15))
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
            currentNextGenChunk.setCellState(0,0,false);
        }
        else if(liveNeighbors == 3)
        {
            currentNextGenChunk.setCellState(0,0,true);
        }
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(0,0,false);
        }

        if(currentNextGenChunk.getCellState(0,0))
        {
            if(topChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX(),currentChunk.getY()-1);
                nextGenChunkList.push_back(temp);
            }
            if(leftChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()-1,currentChunk.getY());
                nextGenChunkList.push_back(temp);
            }
            if(topLeftChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()-1,currentChunk.getY()-1);
                nextGenChunkList.push_back(temp);
            }
        }

        //Check top right corner
        liveNeighbors = 0;
        if(currentChunk.getCellState(0,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(1,15))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(1,14))
        {
            liveNeighbors += 1;
        }
        if(topChunk != NULL)
        {
            if(topChunk->getCellState(15,14))
            {
                liveNeighbors += 1;
            }
            if(topChunk->getCellState(15,15))
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
            if(rightChunk->getCellState(1,0))
            {
                liveNeighbors += 1;
            }
        }
        if(topRightChunk != NULL)
        {
            if(topRightChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            currentNextGenChunk.setCellState(0,15,false);
        }
        else if(liveNeighbors == 3)
        {
            currentNextGenChunk.setCellState(0,15,true);
        }
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(0,15,false);
        }

        if(currentNextGenChunk.getCellState(0,15))
        {
            if(topChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX(),currentChunk.getY()-1);
                nextGenChunkList.push_back(temp);
            }
            if(rightChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()+1,currentChunk.getY());
                nextGenChunkList.push_back(temp);
            }
            if(topRightChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()+1,currentChunk.getY()-1);
                nextGenChunkList.push_back(temp);
            }
        }

        //Check bottom left corner
        liveNeighbors = 0;
        if(currentChunk.getCellState(15,1))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(14,0))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(14,1))
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
            if(leftChunk->getCellState(15,15))
            {
                liveNeighbors += 1;
            }
            if(leftChunk->getCellState(14,15))
            {
                liveNeighbors += 1;
            }
        }
        if(bottomLeftChunk != NULL)
        {
            if(bottomLeftChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            currentNextGenChunk.setCellState(15,0,false);
        }
        else if(liveNeighbors == 3)
        {
            currentNextGenChunk.setCellState(15,0,true);
        }
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(15,0,false);
        }

        if(currentNextGenChunk.getCellState(15,0))
        {
            if(bottomChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX(),currentChunk.getY()+1);
                nextGenChunkList.push_back(temp);
            }
            if(leftChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()-1,currentChunk.getY());
                nextGenChunkList.push_back(temp);
            }
            if(bottomLeftChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()-1,currentChunk.getY()+1);
                nextGenChunkList.push_back(temp);
            }
        }

        //Check bottom right corner
        liveNeighbors = 0;
        if(currentChunk.getCellState(15,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(14,14))
        {
            liveNeighbors += 1;
        }
        if(currentChunk.getCellState(14,15))
        {
            liveNeighbors += 1;
        }
        if(bottomChunk != NULL)
        {
            if(bottomChunk->getCellState(0,15))
            {
                liveNeighbors += 1;
            }
            if(bottomChunk->getCellState(0,14))
            {
                liveNeighbors += 1;
            }
        }
        if(rightChunk != NULL)
        {
            if(rightChunk->getCellState(15,0))
            {
                liveNeighbors += 1;
            }
            if(rightChunk->getCellState(14,0))
            {
                liveNeighbors += 1;
            }
        }
        if(bottomRightChunk != NULL)
        {
            if(bottomRightChunk->getCellState(0,0))
            {
                liveNeighbors += 1;
            }
        }

        if(liveNeighbors < 2)
        {
            currentNextGenChunk.setCellState(15,15,false);
        }
        else if(liveNeighbors == 3)
        {
            currentNextGenChunk.setCellState(15,15,true);
        }
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(15,15,false);
        }

        if(currentNextGenChunk.getCellState(15,15))
        {
            if(bottomChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX(),currentChunk.getY()+1);
                nextGenChunkList.push_back(temp);
            }
            if(rightChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()+1,currentChunk.getY());
                nextGenChunkList.push_back(temp);
            }
            if(bottomRightChunk == NULL)
            {
                LifeChunk temp(currentChunk.getX()+1,currentChunk.getY()+1);
                nextGenChunkList.push_back(temp);
            }
        }

        /////////////////////
        //END CORNER CHECKS//
        /////////////////////

        nextGenChunkList[i] = currentNextGenChunk;
    }

    std::cout << "Swapping generation vectors..." << std::endl;

    chunkList.swap(nextGenChunkList);
    nextGenChunkList.clear();

    std::cout << "Finished simulating generation." << std::endl;
}

void LifeSimRunner::randomize()
{
    chunkList.resize(0);
    LifeChunk temp(3,2);
    chunkList.push_back(temp);
    temp.setX(4);
    chunkList.push_back(temp);
    temp.setY(3);
    chunkList.push_back(temp);
    temp.setX(3);
    chunkList.push_back(temp);

    for(int i = 0;i < chunkList.size();i++)
    {
        for(int j = 0;j < 16;j++)
        {
            for(int k = 0;k < 16;k++)
            {
                if(rand() % 3 == 1)
                {
                    chunkList.at(i).setCellState(j,k,true);
                    std::cout << "Seeded a live cell."  << std::endl;
                }
            }
        }
    }
}

void LifeSimRunner::glider()
{
    chunkList.resize(0);
    LifeChunk temp(3,2);
    temp.setCellState(0,1,true);
    temp.setCellState(1,2,true);
    temp.setCellState(2,0,true);
    temp.setCellState(2,1,true);
    temp.setCellState(2,2,true);
    chunkList.push_back(temp);
}

void LifeSimRunner::gliderGun() //initialize the grid to Gosper's Glider Gun
{
    chunkList.resize(0);
    LifeChunk left(2,2);
    left.setCellState(4,0,true);
    left.setCellState(4,1,true);
    left.setCellState(5,0,true);
    left.setCellState(5,1,true);
    left.setCellState(4,10,true);
    left.setCellState(5,10,true);
    left.setCellState(6,10,true);
    left.setCellState(3,11,true);
    left.setCellState(2,12,true);
    left.setCellState(2,13,true);
    left.setCellState(3,15,true);
    left.setCellState(7,15,true);
    left.setCellState(8,13,true);
    left.setCellState(8,12,true);
    left.setCellState(7,11,true);
    left.setCellState(3,15,true);
    left.setCellState(5,14,true);
    chunkList.push_back(left);

    LifeChunk middle(3,2);
    middle.setCellState(4,0,true);
    middle.setCellState(5,0,true);
    middle.setCellState(6,0,true);
    middle.setCellState(5,1,true);
    middle.setCellState(2,4,true);
    middle.setCellState(3,4,true);
    middle.setCellState(4,4,true);
    middle.setCellState(2,5,true);
    middle.setCellState(3,5,true);
    middle.setCellState(4,5,true);
    middle.setCellState(1,6,true);
    middle.setCellState(5,6,true);
    middle.setCellState(0,8,true);
    middle.setCellState(1,8,true);
    middle.setCellState(5,8,true);
    middle.setCellState(6,8,true);
    chunkList.push_back(middle);

    LifeChunk right(4,2);
    right.setCellState(2,2,true);
    right.setCellState(2,3,true);
    right.setCellState(3,2,true);
    right.setCellState(3,3,true);
    chunkList.push_back(right);
}

void LifeSimRunner::pulsar()
{
    LifeChunk temp(3,2);
    temp.setCellState(3,1,true);
    temp.setCellState(4,1,true);
    temp.setCellState(5,1,true);
    temp.setCellState(9,1,true);
    temp.setCellState(10,1,true);
    temp.setCellState(11,1,true);

    temp.setCellState(1,3,true);
    temp.setCellState(13,3,true);
    temp.setCellState(6,3,true);
    temp.setCellState(8,3,true);

    temp.setCellState(1,4,true);
    temp.setCellState(13,4,true);
    temp.setCellState(6,4,true);
    temp.setCellState(8,4,true);

    temp.setCellState(1,5,true);
    temp.setCellState(13,5,true);
    temp.setCellState(6,5,true);
    temp.setCellState(8,5,true);

    temp.setCellState(3,6,true);
    temp.setCellState(4,6,true);
    temp.setCellState(5,6,true);
    temp.setCellState(9,6,true);
    temp.setCellState(10,6,true);
    temp.setCellState(11,6,true);

    temp.setCellState(3,8,true);
    temp.setCellState(4,8,true);
    temp.setCellState(5,8,true);
    temp.setCellState(9,8,true);
    temp.setCellState(10,8,true);
    temp.setCellState(11,8,true);

    temp.setCellState(1,9,true);
    temp.setCellState(13,9,true);
    temp.setCellState(6,9,true);
    temp.setCellState(8,9,true);

    temp.setCellState(1,10,true);
    temp.setCellState(13,10,true);
    temp.setCellState(6,10,true);
    temp.setCellState(8,10,true);

    temp.setCellState(1,11,true);
    temp.setCellState(13,11,true);
    temp.setCellState(6,11,true);
    temp.setCellState(8,11,true);

    temp.setCellState(3,13,true);
    temp.setCellState(4,13,true);
    temp.setCellState(5,13,true);
    temp.setCellState(9,13,true);
    temp.setCellState(10,13,true);
    temp.setCellState(11,13,true);
    chunkList.push_back(temp);
}

void LifeSimRunner::line()
{
    chunkList.resize(0);

    LifeChunk left(3,2);
    LifeChunk middle(4,2);
    LifeChunk right(5,2);

    left.setCellState(14,1,true);
    left.setCellState(14,2,true);
    left.setCellState(14,3,true);
    left.setCellState(14,4,true);
    left.setCellState(14,5,true);
    left.setCellState(14,6,true);
    left.setCellState(14,7,true);
    left.setCellState(14,8,true);
    left.setCellState(14,9,true);
    left.setCellState(14,10,true);
    left.setCellState(14,11,true);
    left.setCellState(14,12,true);
    left.setCellState(14,13,true);
    left.setCellState(14,14,true);
    left.setCellState(14,15,true);

    middle.setCellState(14,0,true);
    middle.setCellState(14,1,true);
    middle.setCellState(14,2,true);
    middle.setCellState(14,3,true);
    middle.setCellState(14,4,true);
    middle.setCellState(14,5,true);
    middle.setCellState(14,6,true);
    middle.setCellState(14,7,true);
    middle.setCellState(14,8,true);
    middle.setCellState(14,9,true);
    middle.setCellState(14,10,true);
    middle.setCellState(14,11,true);
    middle.setCellState(14,12,true);
    middle.setCellState(14,13,true);
    middle.setCellState(14,14,true);
    middle.setCellState(14,15,true);

    right.setCellState(14,0,true);
    right.setCellState(14,1,true);
    right.setCellState(14,2,true);
    right.setCellState(14,3,true);
    right.setCellState(14,4,true);
    right.setCellState(14,5,true);
    right.setCellState(14,6,true);
    right.setCellState(14,7,true);
    right.setCellState(14,8,true);
    right.setCellState(14,9,true);
    right.setCellState(14,10,true);
    right.setCellState(14,11,true);
    right.setCellState(14,12,true);
    right.setCellState(14,13,true);
    right.setCellState(14,14,true);

    chunkList.push_back(left);
    chunkList.push_back(middle);
    chunkList.push_back(right);
}

void LifeSimRunner::blockLayer()
{
    chunkList.resize(0);
    LifeChunk temp(3,2);

    temp.setCellState(6,1,true);

    temp.setCellState(5,3,true);
    temp.setCellState(6,3,true);

    temp.setCellState(2,5,true);
    temp.setCellState(3,5,true);
    temp.setCellState(4,5,true);

    temp.setCellState(1,7,true);
    temp.setCellState(2,7,true);
    temp.setCellState(3,7,true);

    temp.setCellState(2,8,true);

    chunkList.push_back(temp);
}

void LifeSimRunner::pentomino()
{
    chunkList.resize(0);
    LifeChunk temp(3,2);

    temp.setCellState(2,1,true);

    temp.setCellState(1,2,true);
    temp.setCellState(2,2,true);
    temp.setCellState(3,2,true);

    temp.setCellState(1,3,true);

    chunkList.push_back(temp);
}

void LifeSimRunner::diehard()
{
    chunkList.resize(0);
    LifeChunk temp(3,2);

    temp.setCellState(2,1,true);

    temp.setCellState(2,2,true);
    temp.setCellState(3,2,true);

    temp.setCellState(3,6,true);

    temp.setCellState(1,7,true);
    temp.setCellState(3,7,true);

    temp.setCellState(3,8,true);

    chunkList.push_back(temp);
}

std::vector<LifeChunk> *LifeSimRunner::getChunks()
{
    return &chunkList;
}
