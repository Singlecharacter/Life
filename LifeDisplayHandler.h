#ifndef LIFEDISPLAYHANDLER_H
#define LIFEDISPLAYHANDLER_H

#include <vector>
#include <SDL.h>
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

    void drawChunks(std::vector<LifeChunk> displayChunks);

private:

    SDL_Window *lifeWindow;
    SDL_Renderer *lifeRenderer;
    SDL_Texture *cellTexture;
    SDL_Surface *cellSurface;

    int renderX, renderY;
};

#endif // LIFEDISPLAYHANDLER_H
