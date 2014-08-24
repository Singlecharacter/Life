#include "LifeDisplayHandler.h"

LifeDisplayHandler::LifeDisplayHandler() : renderX(0), renderY(0)
{
    lifeWindow = SDL_CreateWindow("The Game of Life",0,0,1024,768,SDL_WINDOW_OPENGL);
    lifeRenderer = SDL_CreateRenderer(lifeWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    cellSurface = SDL_LoadBMP("cell.bmp");
    cellTexture = SDL_CreateTextureFromSurface(lifeRenderer,cellSurface);
    SDL_FreeSurface(cellSurface);
}

LifeDisplayHandler::~LifeDisplayHandler()
{

}

int LifeDisplayHandler::getRenderX()
{
    return renderX;
}

void LifeDisplayHandler::setRenderX(int newRenderX)
{
    renderX = newRenderX;
}

int LifeDisplayHandler::getRenderY()
{
    return renderY;
}

void LifeDisplayHandler::setRenderY(int newRenderY)
{
    renderY = newRenderY;
}

void LifeDisplayHandler::drawChunks(std::vector<LifeChunk> displayChunks)
{
    SDL_RenderClear(lifeRenderer);
    int drawX = 0;
    int drawY = 0;
    for(int i = 0;i < displayChunks.size();i++)
    {
        LifeChunk *currentChunk = &displayChunks.at(i);
        if(currentChunk->getX() > 0 && currentChunk->getY() > 0)
        {
            for(int j = 0;j < 16;j++)
            {
                for(int k = 0;k < 16;k++)
                {
                    if(currentChunk->getCellState(j,k))
                    {
                        drawX = currentChunk->getX()*128;
                        drawX += 8*j;

                        drawY = currentChunk->getY()*128;
                        drawY += 8*k;

                        SDL_Rect *tempRect = new SDL_Rect();
                        tempRect->x = drawX - renderX;
                        tempRect->y = drawY - renderY;
                        tempRect->w = 8;
                        tempRect->h = 8;
                        SDL_RenderCopy(lifeRenderer,cellTexture,NULL,tempRect);
                    }
                }
            }
        }
        else if(currentChunk->getX() > 0 && currentChunk->getY() < 0)
        {
            for(int j = 0;j < 16;j++)
            {
                for(int k = 0;k < 16;k++)
                {
                    if(currentChunk->getCellState(j,k))
                    {
                        drawX = currentChunk->getX()*128;
                        drawX += 8*j;

                        drawY = currentChunk->getY()*(-128);
                        drawY += 8*k;

                        SDL_Rect *tempRect = new SDL_Rect();
                        tempRect->x = drawX - renderX;
                        tempRect->y = drawY - renderY;
                        tempRect->w = 8;
                        tempRect->h = 8;
                        SDL_RenderCopy(lifeRenderer,cellTexture,NULL,tempRect);
                    }
                }
            }
        }
        else if(currentChunk->getX() < 0 && currentChunk->getY() < 0)
        {
            for(int j = 0;j < 16;j++)
            {
                for(int k = 0;k < 16;k++)
                {
                    if(currentChunk->getCellState(j,k))
                    {
                        drawX = currentChunk->getX()*(-128);
                        drawX += 8*j;

                        drawY = currentChunk->getY()*(-128);
                        drawY += 8*k;

                        SDL_Rect *tempRect = new SDL_Rect();
                        tempRect->x = drawX - renderX;
                        tempRect->y = drawY - renderY;
                        tempRect->w = 8;
                        tempRect->h = 8;
                        SDL_RenderCopy(lifeRenderer,cellTexture,NULL,tempRect);
                    }
                }
            }
        }
        else if(currentChunk->getX() < 0 && currentChunk->getY() > 0)
        {
            for(int j = 0;j < 16;j++)
            {
                for(int k = 0;k < 16;k++)
                {
                    if(currentChunk->getCellState(j,k))
                    {
                        drawX = currentChunk->getX()*(-128);
                        drawX += 8*j;

                        drawY = currentChunk->getY()*128;
                        drawY += 8*k;

                        SDL_Rect *tempRect = new SDL_Rect();
                        tempRect->x = drawX - renderX;
                        tempRect->y = drawY - renderY;
                        tempRect->w = 8;
                        tempRect->h = 8;
                        SDL_RenderCopy(lifeRenderer,cellTexture,NULL,tempRect);
                    }
                }
            }
        }
    }

    SDL_RenderPresent(lifeRenderer);
}
