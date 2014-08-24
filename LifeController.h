#ifndef LIFECONTROLLER_H
#define LIFECONTROLLER_H

#include <SDL.h>
#include <ctime>
#include <cstdlib>

#include "LifeSimRunner.h"
#include "LifeDisplayHandler.h"

class LifeController
{
public:

    LifeController(std::string fname);
    ~LifeController();

    void runLife();
    void runLife(int generations);

private:

    LifeDisplayHandler *display;
    LifeSimRunner *simRunner;

    bool paused;
};

#endif // LIFECONTROLLER_H
