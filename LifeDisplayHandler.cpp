#include "LifeDisplayHandler.h"

LifeDisplayHandler::LifeDisplayHandler() : renderX(0), renderY(0), seizureModeActive(false)
{
    lifeWindow = SDL_CreateWindow("The Game of Life",32,32,1024,768,SDL_WINDOW_OPENGL);
    lifeRenderer = SDL_CreateRenderer(lifeWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(lifeRenderer,0x00,0x00,0x00,0xFF);
    SDL_RenderClear(lifeRenderer);
    SDL_RenderPresent(lifeRenderer);

    cellSurface = SDL_CreateRGBSurface(0,8,8,32,0,0,0,0);
    SDL_FillRect(cellSurface,NULL,SDL_MapRGB(cellSurface->format,0xFF,0xFF,0xFF));
    cellTexture = SDL_CreateTextureFromSurface(lifeRenderer,cellSurface);
}

LifeDisplayHandler::~LifeDisplayHandler()
{
    SDL_FreeSurface(cellSurface);
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

void LifeDisplayHandler::drawChunks(std::vector<LifeChunk> *displayChunks)
{
    std::cout << "Starting chunk display." << std::endl;
    SDL_RenderClear(lifeRenderer);
    int drawX = 0;
    int drawY = 0;

    for(int i = 0;i < displayChunks->size();i++)
    {
        SDL_SetRenderDrawColor(lifeRenderer,0x00,0x00,0x00,0xFF);
        if(seizureModeActive)
        {
            SDL_FreeSurface(cellSurface);
            delete cellSurface;
            delete cellTexture;
            cellSurface = SDL_CreateRGBSurface(0,8,8,32,0,0,0,0);
            SDL_FillRect(cellSurface,NULL,SDL_MapRGB(cellSurface->format,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF));
            cellTexture = SDL_CreateTextureFromSurface(lifeRenderer,cellSurface);
        }
        std::cout << "Displaying chunk " << i+1 << " of " << displayChunks->size() << "..." << std::endl;
        LifeChunk *currentChunk = &(displayChunks->at(i));
        if(currentChunk == NULL)
        {
            std::cout << "ERROR DISPLAYING CHUNKS" << std::endl;
            break;
        }
        for(int j = 0;j < 16;j++)
        {
            for(int k = 0;k < 16;k++)
            {
                if(currentChunk->getCellState(j,k))
                {
                    drawX = currentChunk->getX()*128;
                    drawX += 8*k;

                    drawY = currentChunk->getY()*128;
                    drawY += 8*j;

                    SDL_Rect *tempRect = new SDL_Rect();
                    tempRect->x = drawX - renderX;
                    tempRect->y = drawY - renderY;
                    tempRect->w = 8;
                    tempRect->h = 8;
                    SDL_RenderCopy(lifeRenderer,cellTexture,NULL,tempRect);
                    delete tempRect;
                }
            }
        }
    }

    SDL_RenderPresent(lifeRenderer);
    std::cout << "Finished chunk display." << std::endl;
}

void LifeDisplayHandler::drawChunkBoundaries(std::vector<LifeChunk> *displayChunks)
{
    SDL_Surface *boundSurface = SDL_CreateRGBSurface(0,128,128,32,0,0,0,0);
    SDL_FillRect(boundSurface,NULL,SDL_MapRGB(boundSurface->format,rand() % 0xFF,rand() % 0xFF,rand() % 0xFF));
    SDL_Texture *boundTexture = SDL_CreateTextureFromSurface(lifeRenderer,boundSurface);

    SDL_RenderClear(lifeRenderer);

    int drawX = 0;
    int drawY = 0;
    for(int i = 0;i < displayChunks->size();i++)
    {
        drawX = displayChunks->at(i).getX()*128;
        drawY = displayChunks->at(i).getY()*128;

        SDL_Rect drawRect;
        drawRect.x = drawX - renderX;
        drawRect.y = drawY - renderY;
        drawRect.w = 128;
        drawRect.h = 128;
        SDL_RenderCopy(lifeRenderer,boundTexture,NULL,&drawRect);
    }
    SDL_RenderPresent(lifeRenderer);
    delete boundTexture;
    SDL_FreeSurface(boundSurface);
    delete boundSurface;
}

bool LifeDisplayHandler::getSeizureModeActive()
{
    return seizureModeActive;
}

void LifeDisplayHandler::setSeizureModeActive(bool b)
{
    seizureModeActive = b;
    if(b == false)
    {
        SDL_FreeSurface(cellSurface);
        delete cellSurface;
        delete cellTexture;
        cellSurface = SDL_CreateRGBSurface(0,8,8,32,0,0,0,0);
        SDL_FillRect(cellSurface,NULL,SDL_MapRGB(cellSurface->format,0xFF,0xFF,0xFF));
        cellTexture = SDL_CreateTextureFromSurface(lifeRenderer,cellSurface);
    }
}
