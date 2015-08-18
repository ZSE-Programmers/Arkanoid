#include "Fps.h"

Fps::Fps()
{
    FPS = 60;
    std::cout << "Max FPS: "<< FPS << std::endl;
}

Fps::~Fps()
{
}

void Fps::Start()
{
    m_startTicks = SDL_GetTicks();
}

void Fps::Delay()
{
    if (1000 / FPS > SDL_GetTicks() - m_startTicks)
    {
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - m_startTicks));
    }
}