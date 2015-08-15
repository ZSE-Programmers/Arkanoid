#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

class Level
{
public:
    Level();
    ~Level();

    // Getters
    std::vector <std::string>& GetLevelData() { return m_levelData; }
    std::vector <glm::vec2>& GetLevelPosition() { return m_levelPosition; }
    std::vector <glm::vec2>& GetBricksPosition() { return m_bricksPosition; }
    std::vector <glm::vec2>& GetUpgradesPosition() { return m_upgradesPosition; }
    glm::vec2& GetPlayerPosition() { return m_playerPosition; }
    int GetPlayerLenght() { return m_playerLenght; }
    glm::vec2& GetBallPosition() { return m_ballPosition; }

    int GetSizeVecBricks(){ return m_bricksPosition.size(); }

    //Setters

    

private:
    std::vector <std::string> m_levelData;

    std::vector <glm::vec2> m_levelPosition;

    std::vector <glm::vec2> m_bricksPosition;

    std::vector <glm::vec2> m_upgradesPosition; 

    glm::vec2 m_playerPosition;
    int m_playerLenght;

    glm::vec2 m_ballPosition;

    float TILE_WIDTH;
};

