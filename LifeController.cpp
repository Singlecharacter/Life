#include "LifeController.h"

LifeController::LifeController(std::string fname = "") : paused(true)
{
    simRunner = NULL;
    display = NULL;
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    simRunner = new LifeSimRunner(fname);
    display = new LifeDisplayHandler();
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
                    }
                }
                else if(e.key.keysym.sym == SDLK_p)
                {
                    paused = !paused;
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
            display->setRenderY(display->getRenderY()-2);
        }
        if(spressed)
        {
            display->setRenderY(display->getRenderY()+2);
        }
        if(apressed)
        {
            display->setRenderX(display->getRenderX()-2);
        }
        if(dpressed)
        {
            display->setRenderX(display->getRenderX()+2);
        }
    }
}
