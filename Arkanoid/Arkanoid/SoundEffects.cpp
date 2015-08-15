#include "SoundEffects.h"

SoundEffects::SoundEffects(): m_victory(nullptr), m_lose(nullptr), m_colision(nullptr), m_start(nullptr)
{
}


SoundEffects::~SoundEffects()
{
}

void SoundEffects::Init()
{
	m_victory = Mix_LoadMUS("Sound/victory.mp3");
	m_lose = Mix_LoadMUS("Sound/defeat.mp3");
	m_colision = Mix_LoadMUS("Sound/colision.mp3");
	m_start = Mix_LoadMUS("Sound/start_game.mp3");
}

void SoundEffects::PlaySound(int tmp)
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	switch (tmp)
	{
	case 1:
		if (Mix_PlayMusic(m_start, 1) == -1)
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		}
		break;
	case 2:
		if (Mix_PlayMusic(m_colision, 1) == -1)
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		}
		break;
	case 3:
		if (Mix_PlayMusic(m_victory, 1) == -1)
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		}
		break;
	case 4:
		if (Mix_PlayMusic(m_lose, 1) == -1)
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
		}
		break;
	}
}