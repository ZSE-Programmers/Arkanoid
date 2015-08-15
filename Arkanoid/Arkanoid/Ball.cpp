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
    
    
    if (CollideWithLevel(levelData))
    {
        return true;
    }
    if (CollideWithBricks(levelData, bricksPosition))
    {
        return true;
    }
    if (CollideWithPlayer(startPos, endPos))
    {
        return true;
    }
    return false; //failed
}

bool Ball::CollideWithLevel(std::vector <std::string>& levelData)
{
    glm::ivec2 pos(floor(m_position.x / 32.0f), floor(m_position.y / 32.0f));

    if (pos.x < 1 || pos.x >= levelData[0].size() - 2)
    {
        m_direction.x = -m_direction.x;
        return true;
    }
    else if (pos.y < 1 || pos.y >= levelData.size() - 1)
    {
        m_direction.y = -m_direction.y;
        return true;
    }
    return false;
}

bool Ball::CollideWithPlayer(glm::vec2 startPos, glm::vec2 endPos)
{
    glm::vec2 centerBall(m_position.x + BALL_RADIUS, m_position.y + BALL_RADIUS);
    endPos.x += TILE_WIDTH;

    if (centerBall.y + BALL_RADIUS >= startPos.y && centerBall.y < startPos.y)
    {
        if (centerBall.x + BALL_RADIUS > startPos.x && centerBall.x - BALL_RADIUS < endPos.x)
        {
            m_direction.y = -m_direction.y;
            return true;
        }
        else //player failed
        {
            return false;
        }
    }
    else
    {
        return true;
    }






    /*if (m_position.x > startPos.x - 10 && m_position.x  < endPos.x + 15 && m_position.y + BALL_WIDTH >= startPos.y && m_position.y + BALL_RADIUS <= startPos.y)
    {
        m_direction.y = -m_direction.y;
        return true;
    }
    else if (m_position.y > startPos.y)
    { 
        m_soundEffect->PlaySound(4);
        return false;
    }

    return true;*/
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

    /*if (levelData[gridPosition.y][gridPosition.x] == '1')
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
    return false;*/
}

int Ball::Distance(glm::ivec2 value1, glm::ivec2 value2) //Distance^2
{
    return pow(value1.x - value2.x, 2) + pow(value1.y - value2.y, 2);
}