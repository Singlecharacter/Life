#include "LifeSimRunner.h"

LifeSimRunner::LifeSimRunner()
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
    std::cout << "Starting generation simulation." << std::endl;
    std::vector<LifeChunk> nextGenChunkList = chunkList;
    //Loop through each chunk, performing cell state change checks
    for(int i = 0;i < chunkList.size();i++)
    {
        std::cout << "Checking chunk " << i+1 << " of " << chunkList.size() << "..." << std::endl;
        LifeChunk currentChunk = chunkList.at(i);
        LifeChunk currentNextGenChunk = nextGenChunkList.at(i);

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
            if(topChunk->getCellState(14,0))
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
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(0,0,false);
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
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(0,15,false);
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
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(15,0,false);
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
        else if(liveNeighbors > 3)
        {
            currentNextGenChunk.setCellState(15,15,false);
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
                if(rand() % 2 == 1)
                {
                    chunkList.at(i).setCellState(j,k,true);
                    std::cout << "Seeded a live cell."  << std::endl;
                }
            }
        }
    }
}

std::vector<LifeChunk> *LifeSimRunner::getChunks()
{
    return &chunkList;
}
