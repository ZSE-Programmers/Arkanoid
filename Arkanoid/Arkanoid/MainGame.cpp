#include "MainGame.h"


MainGame::MainGame() 
{
    m_gameState = GameState::PLAY; 
    m_renderer = nullptr;
    m_levelTexture = nullptr;
    m_playerTexture = nullptr;
    m_ballTexture = nullptr;
}


MainGame::~MainGame()
{
}

void MainGame::Run()
{
    InitSystems();
    GameLoop();
}

void MainGame::InitSystems()
{
    m_window.Create(800, 600);
    m_renderer = m_window.GetRenderer();
    m_levelTexture = m_sprite.LoadTexture("Textures/light_bricks.png", m_renderer);
    m_playerTexture = m_sprite.LoadTexture("Textures/light.png", m_renderer);
    m_ballTexture = m_sprite.LoadTexture("Textures/circle.png", m_renderer);
    m_bricksTexture = m_sprite.LoadTexture("Textures/box.png", m_renderer);
    m_upgradesTexture = m_sprite.LoadTexture("Textures/box1.png", m_renderer);

	m_soundEffects.Init();

    m_levelPosition = m_level.GetLevelPosition();

    m_player.Init(0.2f, m_level.GetPlayerPosition(), m_level.GetPlayerLenght(), &m_inputManager);

    m_ball.Init(m_level.GetBallPosition(), glm::vec2(0.5f, 0.5f), 0.2f, &m_soundEffects);

	m_bonus.Init(&m_player, &m_playerStats);
}

void MainGame::ProcessInput()
{
    SDL_Event tmp_event;
    while (SDL_PollEvent(&tmp_event))
    {
        switch (tmp_event.type)
        {
        case SDL_QUIT:
            m_gameState = GameState::EXIT;
            break;
        case SDL_MOUSEMOTION:
            //std::cout << tmp_event.motion.x << " " << tmp_event.motion.y << std::endl;
            break;
        case SDL_KEYDOWN:
            m_inputManager.PressKey(tmp_event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            m_inputManager.ReleaseKey(tmp_event.key.keysym.sym);
            break;
        }
    }
}

void MainGame::GameLoop()
{
    m_playerStats.ShowStats();
    while (m_gameState != GameState::EXIT)
    {
        ProcessInput();
        Draw();
        Update();
    }
}

void MainGame::Draw()
{
    SDL_RenderClear(m_renderer);

    // Drawing level
    for (int i = 0; i < m_levelPosition.size(); i++)
    {
        SDL_Rect destRect;
        destRect.x = m_levelPosition[i].x;
        destRect.y = m_levelPosition[i].y;
        destRect.w = TILE_WIDTH;
        destRect.h = TILE_WIDTH;
        SDL_RenderCopy(m_renderer, m_levelTexture, 0, &destRect);
    }
    
    // Drawing bricks
    std::vector <glm::vec2> tmp_bricksPosition = m_level.GetBricksPosition();
    for (int i = 0; i < tmp_bricksPosition.size(); i++)
    {
        SDL_Rect destRect;
        destRect.x = tmp_bricksPosition[i].x;
        destRect.y = tmp_bricksPosition[i].y;
        destRect.w = TILE_WIDTH;
        destRect.h = TILE_WIDTH;
        SDL_RenderCopy(m_renderer, m_bricksTexture, 0, &destRect);
    }

    // Drawing upgrades
    std::vector <glm::vec2> tmp_upgradesPosition = m_level.GetUpgradesPosition();
    for (int i = 0; i < tmp_upgradesPosition.size(); i++)
    {
        SDL_Rect destRect;
        destRect.x = tmp_upgradesPosition[i].x;
        destRect.y = tmp_upgradesPosition[i].y;
        destRect.w = TILE_WIDTH;
        destRect.h = TILE_WIDTH;
        SDL_RenderCopy(m_renderer, m_upgradesTexture, 0, &destRect);
    }
    
    // Draw player
    std::vector <glm::vec2> platformPos = m_player.GetPlatformPosition();
    for (int i = 0; i < platformPos.size(); i++)
    {
        SDL_Rect destRect;
        destRect.x = platformPos[i].x;
        destRect.y = platformPos[i].y;
        destRect.w = TILE_WIDTH;
        destRect.h = TILE_WIDTH;
        SDL_RenderCopy(m_renderer, m_playerTexture, 0, &destRect);
    }
    
    // Draw ball
    glm::vec2 ballPosition = m_ball.GetPosition();
    SDL_Rect destVec;
    destVec.x = ballPosition.x;
    destVec.y = ballPosition.y;
    destVec.w = 2 * m_ball.GetRadius();
    destVec.h = 2 * m_ball.GetRadius();
    SDL_RenderCopy(m_renderer, m_ballTexture, 0, &destVec);

    // Rendering everything to screen
    SDL_RenderPresent(m_renderer);
}

void MainGame::Update()
{
    m_player.Update();
    if (m_ball.Update(m_level.GetLevelData(), m_player.GetStartPos(), m_player.GetEndPos(), m_level.GetBricksPosition(), m_level.GetUpgradesPosition()))
    {
        if (m_ball.CollideWithUpgrades(m_level.GetUpgradesPosition()))
        {
            m_bonus.ActivateBonus();
        }
    }
    else
    {
        m_gameState = GameState::EXIT; 
    }
}