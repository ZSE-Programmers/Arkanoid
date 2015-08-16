#include "Ball.h"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <math.h>

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


bool Ball::Update(std::vector <std::string>& levelData, glm::vec2 startPos, glm::vec2 endPos, std::vector <glm::vec2>& bricksPosition, std::vector <glm::vec2>& upgradesPosition)
{
    m_position += m_direction * m_speed;
    
    // Colliding with player
    if (CollideWithPlayer(startPos, endPos))
    {
        return true;
    }

    // Colliding with level
    if (CollideWithLevel(levelData))
    {
        return true;
    }
    // Colliding with bricks
    if (CollideWithBricks(levelData, bricksPosition, upgradesPosition))
    {
        return true;
    }
    //Colliding with upgrades

    // Check if ball is under player
    if (CheckLose(startPos))
    {
        return false;
    }
    return true; 
}

bool Ball::CollideWithLevel(std::vector <std::string>& levelData)
{
    glm::ivec2 pos(floor(m_position.x / 32.0f), floor(m_position.y / 32.0f));

    if (pos.x < 1 || pos.x >= levelData[0].size() - 2)
    {
        m_direction.x = -m_direction.x;
        return true;
    }
    else if (pos.y < 1)
    {
        m_direction.y = -m_direction.y;
        return true;
    }
    return false;
}

bool Ball::CollideWithPlayer(glm::vec2 startPos, glm::vec2 endPos)
{
    glm::vec2 centerBallPos = glm::vec2(m_position + BALL_RADIUS);
    if (centerBallPos.y + BALL_RADIUS >= startPos.y)
    {
        if (centerBallPos.x >= startPos.x - 10 && centerBallPos.x <= endPos.x + TILE_WIDTH + 10)
        {
            m_direction.y = -m_direction.y;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false; 
}

bool Ball::CollideWithBricks(std::vector <std::string>& levelData, std::vector <glm::vec2>& bricksPosition, std::vector <glm::vec2>& upgradesPosition)
{
    // Direction flag
    int dirFlag = 0;
    if (m_direction.x < 0)
    {
        if (m_direction.y < 0)
        {
            dirFlag = 0;
        }
        else
        {
            dirFlag = 1;
        }
    }
    else
    {
        if (m_direction.y < 0)
        {
            dirFlag = 2;
        }
        else
        {
            dirFlag = 3;
        }
    }

    // Center ball position
    glm::vec2 centerBallPos = { m_position.x + BALL_RADIUS, m_position.y + BALL_RADIUS };
    // Minimum distance between objects
    float MIN_DIST = BALL_RADIUS + TILE_RADIUS;

    // Looping trough bricks position vector
    for (int i = 0; i < bricksPosition.size(); ++i)
    {
        // Center brick position
        glm::vec2 centerBrickPosition = { bricksPosition[i].x + TILE_RADIUS, bricksPosition[i].y + TILE_RADIUS};
        // Distance between two objects
        glm::vec2 distVec = centerBallPos - centerBrickPosition;
        float distance = glm::length(distVec);

        // If distance is less then minimum distance
        if (distance <= MIN_DIST)
        {
            CollideBrick(bricksPosition, dirFlag);
            return true;
        }
    }

    return false;
}

bool Ball::CollideBrick(std::vector <glm::vec2>& bricksPosition, int dirFlag)
{
    /*  A | B | C
    - - - - -
    D | O | F
    - - - - -
    G | H | I  */
    glm::vec2 cornerPosition;
    glm::vec2 centerBall(floor(m_position.x + BALL_RADIUS), floor(m_position.y + BALL_RADIUS));

    //get all RIGHT & BOTTOM bricks corners
    for (int i = 0; i < bricksPosition.size(); i++)
    {
        if (dirFlag == 0)
        {
            cornerPosition = { bricksPosition[i].x + TILE_WIDTH, bricksPosition[i].y + TILE_WIDTH };

            if (centerBall.y - BALL_RADIUS <= cornerPosition.y
                && centerBall.y > cornerPosition.y
                && centerBall.x < cornerPosition.x
                && centerBall.x > cornerPosition.x - TILE_WIDTH)//B
            {
                m_direction.y = -m_direction.y;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitB" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
            else if (centerBall.x - BALL_RADIUS <= cornerPosition.x
                && centerBall.x > cornerPosition.x
                && centerBall.y < cornerPosition.y
                && centerBall.y > cornerPosition.y - TILE_WIDTH)//D
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitD" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
        }
        else if (dirFlag == 1)
        {
            cornerPosition = { bricksPosition[i].x + TILE_WIDTH, bricksPosition[i].y };

            if (centerBall.y + BALL_RADIUS >= cornerPosition.y
                && centerBall.y < cornerPosition.y
                && centerBall.x < cornerPosition.x
                && centerBall.x > cornerPosition.x - TILE_WIDTH)//H
            {
                m_direction.y = -m_direction.y;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitH" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
            else if (centerBall.x - BALL_RADIUS <= cornerPosition.x
                && centerBall.x > cornerPosition.x
                && centerBall.y < cornerPosition.y + TILE_WIDTH
                && centerBall.y > cornerPosition.y)//D
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitD" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
        }
        else if (dirFlag == 2)
        {
            cornerPosition = { bricksPosition[i].x, bricksPosition[i].y + TILE_WIDTH };

            if (centerBall.y - BALL_RADIUS <= cornerPosition.y
                && centerBall.y > cornerPosition.y
                && centerBall.x < cornerPosition.x + TILE_WIDTH
                && centerBall.x > cornerPosition.x)//B
            {
                m_direction.y = -m_direction.y;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitB" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
            else if (centerBall.x + BALL_RADIUS >= cornerPosition.x
                && centerBall.x < cornerPosition.x
                && centerBall.y < cornerPosition.y
                && centerBall.y > cornerPosition.y - TILE_WIDTH)//F
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitF" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
        }
        else if (dirFlag == 3)
        {
            cornerPosition = { bricksPosition[i].x, bricksPosition[i].y };

            if (centerBall.y + BALL_RADIUS >= cornerPosition.y
                && centerBall.y < cornerPosition.y
                && centerBall.x < cornerPosition.x + TILE_WIDTH
                && centerBall.x > cornerPosition.x)//H
            {
                m_direction.y = -m_direction.y;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitH" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
            else if (centerBall.x + BALL_RADIUS >= cornerPosition.x
                && centerBall.x < cornerPosition.x
                && centerBall.y < cornerPosition.y + TILE_WIDTH
                && centerBall.y > cornerPosition.y)//F
            {
                m_direction.x = -m_direction.x;
                bricksPosition[i] = bricksPosition.back();
                bricksPosition.pop_back();
                std::cout << "hitF" << std::endl;
                m_soundEffect->PlaySound(2);
                return true;
            }
        }
    }
    return false;
}

bool Ball::CheckLose(glm::vec2& playerPos)
{
    if (m_position.y >= playerPos.y - BALL_RADIUS)
    {
        return true;
    }
    return false;
}

float Ball::Distance(glm::ivec2 value1, glm::ivec2 value2)
{
    return pow(value1.x - value2.x, 2) + pow(value1.y - value2.y, 2);
}

bool Ball::CollideWithUpgrades(std::vector <glm::vec2>& upgradesPosition)
{
    // Direction flag
    int dirFlag = 0;
    if (m_direction.x < 0)
    {
        if (m_direction.y < 0)
        {
            dirFlag = 0;
        }
        else
        {
            dirFlag = 1;
        }
    }
    else
    {
        if (m_direction.y < 0)
        {
            dirFlag = 2;
        }
        else
        {
            dirFlag = 3;
        }
    }

    // Center ball position
    glm::vec2 centerBallPos = { m_position.x + BALL_RADIUS, m_position.y + BALL_RADIUS };
    // Minimum distance between objects
    float MIN_DIST = BALL_RADIUS + TILE_RADIUS;

    // Looping trough bricks position vector
    for (int i = 0; i < upgradesPosition.size(); ++i)
    {
        // Center brick position
        glm::vec2 centerBrickPosition = { upgradesPosition[i].x + TILE_RADIUS, upgradesPosition[i].y + TILE_RADIUS };
        // Distance between two objects
        glm::vec2 distVec = centerBallPos - centerBrickPosition;
        float distance = glm::length(distVec);

        // If distance is less then minimum distance
        if (distance <= MIN_DIST)
        {
            CollideBrick(upgradesPosition, dirFlag);
            return true;
        }
    }
    return false;
}