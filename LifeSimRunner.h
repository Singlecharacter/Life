#ifndef LIFESIMRUNNER_H
#define LIFESIMRUNNER_H

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "LifeChunk.h"

class LifeSimRunner
{
public:

    LifeSimRunner();
    ~LifeSimRunner();

    void simGeneration();

    //The following methods initialize the life board to specific states
    void randomize();
    void glider();
    void gliderGun();
    void pulsar();
    void line();
    void blockLayer();
    void pentomino();
    void diehard();

    std::vector<LifeChunk> *getChunks();

private:

    std::vector<LifeChunk> chunkList;
};

#endif // LIFESIMRUNNER_H
