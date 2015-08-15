#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>

class SoundEffects
{
public:
	SoundEffects();
	~SoundEffects();

	void Init();
	void PlaySound(int);

private:

	Mix_Music* m_start; //1
	Mix_Music* m_colision;//2
	Mix_Music* m_victory;//3
	Mix_Music* m_lose;//4
};