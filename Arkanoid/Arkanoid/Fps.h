#pragma once

#include <SDL/SDL.h>
#include <iostream>

class Fps
{
public:
    Fps();
    ~Fps();
    void Start();
    void Delay();

private:
    int FPS;
    Uint32 m_startTicks;


};