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


bool Ball::Update(std::vector <std::string>& levelData, glm::vec2 startPos, glm::vec2 endPos, std::vector <glm::vec2>& bricksPosition)
{
    m_position += m_direction * m_speed;
    
    // Colliding with level
    if (CollideWithLevel(levelData))
    {
        return true;
    }
    // Colliding with bricks
    if (CollideWithBricks(levelData, bricksPosition))
    {
        return true;
    }
    //Colliding with upgrades

    // Colliding with player
    if (CollideWithPlayer(startPos, endPos))
    {
        return true;
    }
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
        if (centerBallPos.x >= startPos.x && centerBallPos.x <= endPos.x + TILE_WIDTH)
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

bool Ball::CollideWithBricks(std::vector <std::string>& levelData, std::vector <glm::vec2>& bricksPosition)
{
    /*  A | B | C
        - - - - -
        D | O | F
        - - - - -
        G | H | I
    */
    glm::vec2 cornerPosition;
    glm::vec2 centerBall(floor(m_position.x + BALL_RADIUS), floor(m_position.y + BALL_RADIUS));

    if (m_direction.x < 0) //LEFT (ABDGH)
    {
        if (m_direction.y < 0) //TOP (ABD)
        {
            //get all RIGHT & BOTTOM bricks corners
            for (int i = 0; i < bricksPosition.size(); i++)
            {
                cornerPosition = { bricksPosition[i].x + TILE_WIDTH, bricksPosition[i].y + TILE_WIDTH };

                if (Distance(cornerPosition, centerBall) == BALL_RADIUS * BALL_RADIUS) //A
                {
                    if (abs(cornerPosition.x - centerBall.x) > abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.y = -m_direction.y;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) < abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) == abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                        m_direction.y = -m_direction.y;
                    }
                    bricksPosition[i] = bricksPosition.back();
                    bricksPosition.pop_back();
                    std::cout << "hitA" <<std::endl;
                    m_soundEffect->PlaySound(2);
                    return true;
                }

                else if (centerBall.y - BALL_RADIUS <= cornerPosition.y
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
        }



        else //BOTTOM (DGH)
        {
            //get all RIGHT & TOP bricks corners
            for (int i = 0; i < bricksPosition.size(); i++)
            {
                cornerPosition = { bricksPosition[i].x + TILE_WIDTH, bricksPosition[i].y};

                if (Distance(cornerPosition, centerBall) == BALL_RADIUS * BALL_RADIUS) //G
                {
                    if (abs(cornerPosition.x - centerBall.x) > abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.y = -m_direction.y;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) < abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) == abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                        m_direction.y = -m_direction.y;
                    }
                    bricksPosition[i] = bricksPosition.back();
                    bricksPosition.pop_back();
                    std::cout << "hitG" << std::endl;
                    m_soundEffect->PlaySound(2);
                    return true;
                }

                else if (centerBall.y + BALL_RADIUS >= cornerPosition.y
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
        }
    }
    else //RIGHT (BCFHI)
    {
        if (m_direction.y < 0) //TOP (BCF)
        {
            //get all LEFT & BOTTOM bricks corners
            for (int i = 0; i < bricksPosition.size(); i++)
            {
                cornerPosition = { bricksPosition[i].x, bricksPosition[i].y + TILE_WIDTH };

                if (Distance(cornerPosition, centerBall) == BALL_RADIUS * BALL_RADIUS) //C
                {
                    if (abs(cornerPosition.x - centerBall.x) > abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.y = -m_direction.y;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) < abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) == abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                        m_direction.y = -m_direction.y;
                    }
                    bricksPosition[i] = bricksPosition.back();
                    bricksPosition.pop_back();
                    std::cout << "hitC" << std::endl;
                    m_soundEffect->PlaySound(2);
                    return true;
                }

                else if (centerBall.y - BALL_RADIUS <= cornerPosition.y
                    && centerBall.y > cornerPosition.y
                    && centerBall.x < cornerPosition.x + TILE_WIDTH
                    && centerBall.x > cornerPosition.x )//B
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
        }
        else //BOTTOM (FHI)
        {
            //get all LEFT & TOP bricks corners
            for (int i = 0; i < bricksPosition.size(); i++)
            {
                cornerPosition = { bricksPosition[i].x, bricksPosition[i].y };

                if (Distance(cornerPosition, centerBall) == BALL_RADIUS * BALL_RADIUS) //I
                {
                    if (abs(cornerPosition.x - centerBall.x) > abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.y = -m_direction.y;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) < abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                    }
                    else if (abs(cornerPosition.x - centerBall.x) == abs(cornerPosition.y - centerBall.y))
                    {
                        m_direction.x = -m_direction.x;
                        m_direction.y = -m_direction.y;
                    }
                    bricksPosition[i] = bricksPosition.back();
                    bricksPosition.pop_back();
                    std::cout << "hitI" << std::endl;
                    m_soundEffect->PlaySound(2);
                    return true;
                }

                else if (centerBall.y + BALL_RADIUS >= cornerPosition.y
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
}

int Ball::Distance(glm::ivec2 value1, glm::ivec2 value2) //Distance^2
{
    return pow(value1.x - value2.x, 2) + pow(value1.y - value2.y, 2);
}

bool Ball::CheckLose(glm::vec2& playerPos)
{
    if (m_position.y >= playerPos.y - BALL_RADIUS)
    {
        return true;
    }
    return false;
}