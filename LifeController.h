#ifndef LIFECONTROLLER_H
#define LIFECONTROLLER_H

#undef main
#include <SDL.h>
#include <ctime>
#include <cstdlib>

#include "LifeSimRunner.h"
#include "LifeDisplayHandler.h"

class LifeController
{
public:

    LifeController();
    ~LifeController();

    void runLife();
    void runLife(int generations);

private:

    LifeDisplayHandler *display;
    LifeSimRunner *simRunner;

    bool paused;
    bool debug;
};

#endif // LIFECONTROLLER_H
