#pragma once

#include <glm/glm.hpp>
#include <SDL/SDL.h>

#include <vector>

#include "InputManager.h"
#include "Sprite.h"

const float PLATFORM_WIDTH = 32.0f;

class Player
{
public:
    Player();
    ~Player();

    void Init(float speed, glm::vec2 position, int length, InputManager* inputManager);

    void Update();

    std::vector <glm::vec2>& GetPlatformPosition() { return m_platform; }
    glm::vec2& GetStartPos() { return m_platform[0]; }
    glm::vec2& GetEndPos() { return m_platform.back(); }

    void BuildPlatform(glm::vec2 position);
    void ChangePlatformLength(int add);

private:

    SDL_Texture* m_texture;
    InputManager* m_inputManager;
    float m_speed;
    int m_platformLength;
    std::vector <glm::vec2> m_platform;
};