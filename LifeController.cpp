#include "LifeController.h"

LifeController::LifeController() : paused(true), debug(false)
{
    simRunner = NULL;
    display = NULL;
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    simRunner = new LifeSimRunner();
    display = new LifeDisplayHandler();
    display->drawChunks(simRunner->getChunks());
}

LifeController::~LifeController()
{
    delete simRunner;
    delete display;
}

void LifeController::runLife()
{
    bool wpressed = false;
    bool spressed = false;
    bool apressed = false;
    bool dpressed = false;
    while(true)
    {
        if(!paused)
        {
            simRunner->simGeneration();

            if(!debug)
            {
                display->drawChunks(simRunner->getChunks());
            }
            else
            {
                display->drawChunkBoundaries(simRunner->getChunks());
            }
        }
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_SPACE)
                {
                    if(paused)
                    {
                        simRunner->simGeneration();
                        if(!debug)
                        {
                            display->drawChunks(simRunner->getChunks());
                        }
                        else
                        {
                            display->drawChunkBoundaries(simRunner->getChunks());
                        }
                    }
                }
                else if(e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT)
                {
                    debug = !debug;
                    if(!debug)
                    {
                        display->drawChunks(simRunner->getChunks());
                    }
                    else
                    {
                        display->drawChunkBoundaries(simRunner->getChunks());
                    }
                }
                else if(e.key.keysym.sym == SDLK_p)
                {
                    paused = !paused;
                }
                else if(e.key.keysym.sym == SDLK_r)
                {
                    paused = true;
                    debug = false;
                    delete simRunner;
                    simRunner = NULL;
                    simRunner = new LifeSimRunner();
                    display->setRenderX(0);
                    display->setRenderY(0);
                    display->drawChunks(simRunner->getChunks());
                }
                else if(e.key.keysym.sym == SDLK_w)
                {
                    wpressed = true;
                }
                else if(e.key.keysym.sym == SDLK_s)
                {
                    spressed = true;
                }
                else if(e.key.keysym.sym == SDLK_a)
                {
                    apressed = true;
                }
                else if(e.key.keysym.sym == SDLK_d)
                {
                    dpressed = true;
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if(e.key.keysym.sym == SDLK_w)
                {
                    wpressed = false;
                }
                else if(e.key.keysym.sym == SDLK_s)
                {
                    spressed = false;
                }
                else if(e.key.keysym.sym == SDLK_a)
                {
                    apressed = false;
                }
                else if(e.key.keysym.sym == SDLK_d)
                {
                    dpressed = false;
                }
            }
            else if(e.type == SDL_QUIT)
            {
                SDL_Quit();
            }
        }

        if(wpressed)
        {
            display->setRenderY(display->getRenderY()-6);
            if(!debug)
            {
                display->drawChunks(simRunner->getChunks());
            }
            else
            {
                display->drawChunkBoundaries(simRunner->getChunks());
            }
        }
        if(spressed)
        {
            display->setRenderY(display->getRenderY()+6);
            if(!debug)
            {
                display->drawChunks(simRunner->getChunks());
            }
            else
            {
                display->drawChunkBoundaries(simRunner->getChunks());
            }
        }
        if(apressed)
        {
            display->setRenderX(display->getRenderX()-6);
            if(!debug)
            {
                display->drawChunks(simRunner->getChunks());
            }
            else
            {
                display->drawChunkBoundaries(simRunner->getChunks());
            }
        }
        if(dpressed)
        {
            display->setRenderX(display->getRenderX()+6);
            if(!debug)
            {
                display->drawChunks(simRunner->getChunks());
            }
            else
            {
                display->drawChunkBoundaries(simRunner->getChunks());
            }
        }

        SDL_Delay(50);
    }
}
