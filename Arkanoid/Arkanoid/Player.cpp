#include "Player.h"
#include <iostream> //tmp
#include <conio.h>
Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(float speed, glm::vec2 position, int length, InputManager* inputManager)
{
    m_speed = speed;
    m_platformLength = length;
    m_inputManager = inputManager;
    BuildPlatform(position);
}

void Player::Update()
{
    if (m_inputManager->IsKeyPressed(SDLK_a) || m_inputManager->IsKeyPressed(SDLK_LEFT))
    {
        if (m_platform[0].x > 40.0f)
        {
            for (int i = 0; i < m_platform.size(); i++)
            {
                m_platform[i] -= glm::vec2(m_speed, 0.0f); 
            }
        }
    }
    else if (m_inputManager->IsKeyPressed(SDLK_d) || m_inputManager->IsKeyPressed(SDLK_RIGHT))
    {
        if (m_platform.back().x < 728.0f)
        {
            for (int i = 0; i < m_platform.size(); i++)
            {
                m_platform[i] += glm::vec2(m_speed, 0.0f);
            }
        }
    }
}

void Player::BuildPlatform(glm::vec2 position)
{
    for (int i = 0; i < m_platformLength; i++)
    {
        m_platform.push_back(position);
        position.x += PLATFORM_WIDTH;
    }
}

void Player::ChangePlatformLength(int add)
{
    m_platformLength += add;
    glm::vec2 tmp_position = m_platform[0];

    m_platform.clear();

    if (add > 0)
    {
        tmp_position.x -= PLATFORM_WIDTH * add;
        BuildPlatform(tmp_position);
    }
    else
    {
        tmp_position.x = PLATFORM_WIDTH * add;
        BuildPlatform(tmp_position);
    }
}
