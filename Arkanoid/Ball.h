#pragma once
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <vector>
#include <string>

#include "SoundEffects.h"



class Ball
{
public:
    Ball();
    ~Ball();
    void Init(glm::vec2 position, glm::vec2 direction, float speed, SoundEffects* soundEffect);
    bool Update(std::vector <std::string>& levelData, glm::vec2 startPos, glm::vec2 endPos, std::vector <glm::vec2>& bricksPosition);

    glm::vec2& GetPosition() { return m_position; }
    const float GetRadius() { return BALL_RADIUS; }

private:
    bool CollideWithLevel(std::vector <std::string>& levelData);
    bool CollideWithPlayer(glm::vec2 startPos, glm::vec2 endPos);
    bool CollideWithBricks(std::vector <std::string>& levelData, std::vector <glm::vec2>& bricksPosition);


    glm::vec2 m_position;
    glm::vec2 m_direction;
    float m_speed;

    const float BALL_RADIUS = 15.0f;
    const float BALL_WIDTH = 30.0f;
    const float TILE_WIDTH = 32.0f;

    SoundEffects* m_soundEffect;
};

