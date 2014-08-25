#ifndef LIFEDISPLAYHANDLER_H
#define LIFEDISPLAYHANDLER_H

#include <vector>

#undef main
#include <SDL.h>
#include <iostream>
#include "LifeChunk.h"

class LifeDisplayHandler
{
public:

    LifeDisplayHandler();
    ~LifeDisplayHandler();

    int getRenderX();
    void setRenderX(int newRenderX);

    int getRenderY();
    void setRenderY(int newRenderY);

    void drawChunks(std::vector<LifeChunk> *displayChunks);
    void drawChunkBoundaries(std::vector<LifeChunk> *displayChunks);

private:

    SDL_Window *lifeWindow;
    SDL_Renderer *lifeRenderer;
    SDL_Surface *cellSurface;
    SDL_Texture *cellTexture;

    int renderX, renderY;
};

#endif // LIFEDISPLAYHANDLER_H
