#include "Level.h"


Level::Level() : TILE_WIDTH(32.0f)
{
    std::ifstream file;
    std::string input;

    file.open("Levels/level1.txt");
    if (file.fail())
    {
        perror("Levels/level1.txt");
    }

    while (std::getline(file, input))
    {
        m_levelData.push_back(input);
    }

    for (int y = 0; y < m_levelData.size(); y++)
    {
        for (int x = 0; x < m_levelData[y].size(); x++)
        {
            char tile = m_levelData[y][x];

            switch (tile)
            {
            case '#': 
                m_levelPosition.push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
                break;
            case '-':
                if (!m_playerLenght)
                {
                    m_playerPosition = glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH);
                }
                m_playerLenght++;
                break;
            case ',':
                m_ballPosition = glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH);
                break;
            case '1':
                m_bricksPosition.push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
                break;
            case '2':
                m_upgradesPosition.push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
                break;
            }
        }
    }
}

Level::~Level()
{
}

bool Level::Empty()
{
    if (m_bricksPosition.empty() && m_upgradesPosition.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}