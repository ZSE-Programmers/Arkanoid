#include "Ball.h"
#include <iostream>
#include <algorithm>
#include <iostream>

Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::Init(glm::vec2 position, glm::vec2 direction, float speed, SoundEffects* soundEffect)
{
    m_position = position;
    m_direction = direction;
    m_speed = speed;
    m_soundEffect = soundEffect;
}


bool Ball::Update(std::vector <std::string>& levelData, glm::vec2 startPos, glm::vec2 endPos, std::vector <glm::vec2>& bricksPosition)
{
    m_position += m_direction * m_speed;
    CollideWithLevel(levelData);
    if (CollideWithBricks(levelData, bricksPosition))
    {
        //glm::vec2 tilePosition = glm::vec2(floor(m_position.x / TILE_WIDTH), floor(m_position.y / TILE_WIDTH));
        std::cout << "You hit brick!\n";

    }
    if (CollideWithPlayer(startPos, endPos))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Ball::CollideWithLevel(std::vector <std::string>& levelData)
{
    glm::ivec2 pos(floor(m_position.x / 32.0f), floor(m_position.y / 32.0f));

    if (pos.x < 1 || pos.x >= levelData[0].size() - 2)
    {
        m_direction.x = -m_direction.x;
        // Play sound when hit the wall
        //m_soundEffect->PlaySound(1);
        return true;
    }
    else if (pos.y < 1 || pos.y >= levelData.size() - 1)
    {
        m_direction.y = -m_direction.y;
        // Play sound when hit the wall
        //m_soundEffect->PlaySound(1);
        return true;
    }
    return false;
}

bool Ball::CollideWithPlayer(glm::vec2 startPos, glm::vec2 endPos)
{
    if (m_position.x > startPos.x - 10 && m_position.x  < endPos.x + 15 && m_position.y + BALL_WIDTH >= startPos.y && m_position.y + BALL_RADIUS <= startPos.y)
    {
        m_direction.y = -m_direction.y;
        return true;
    }
    else if (m_position.y > startPos.y)
    { 
        m_soundEffect->PlaySound(4);
        return false;
    }

    return true;
}

bool Ball::CollideWithBricks(std::vector <std::string>& levelData, std::vector <glm::vec2>& bricksPosition)
{
    glm::ivec2 gridPosition(floor(m_position.x / TILE_WIDTH), floor(m_position.y) / TILE_WIDTH);
    if (levelData[gridPosition.y][gridPosition.x] == '1')
    {
        levelData[gridPosition.y][gridPosition.x] = '.';

        glm::vec2 tilePosition = glm::vec2(gridPosition.x * TILE_WIDTH, gridPosition.y * TILE_WIDTH);
        for (int i = 0; i < bricksPosition.size(); )
        {
            if (m_position.x <= bricksPosition[i].x + TILE_WIDTH &&
                m_position.y <= bricksPosition[i].y + TILE_WIDTH &&
                m_position.y + BALL_WIDTH >= bricksPosition[i].y)
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                break;
            }
            else if (m_position.x + BALL_WIDTH >= bricksPosition[i].x &&
                m_position.y <= bricksPosition[i].y + TILE_WIDTH &&
                m_position.y + BALL_WIDTH >= bricksPosition[i].y)
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                break;
            }
            else if (m_position.y + BALL_WIDTH >= bricksPosition[i].y &&
                m_position.x + BALL_RADIUS >= bricksPosition[i].x &&
                m_position.x <= bricksPosition[i].x + TILE_WIDTH)
            {
                m_direction.y = -m_direction.y;
            }
            else
            {
                i++;
            }
        }
        return true;
    }
    return false;
}

