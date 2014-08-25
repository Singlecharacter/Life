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

    std::vector<LifeChunk> *getChunks();

private:

    //void readFile(std::string fname);
    void randomize();

    std::vector<LifeChunk> chunkList;
};

#endif // LIFESIMRUNNER_H
