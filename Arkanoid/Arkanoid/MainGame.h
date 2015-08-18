#pragma once
#include "Window.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Level.h"
#include "SoundEffects.h"
#include "Bonus.h"
#include "Player.h"
#include "PlayerStats.h"
#include "Ball.h"
#include "Fps.h"
#include <SDL/SDL_ttf.h>

const float TILE_WIDTH = 32.0f;

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void Run();
   
private:
    void InitSystems();
    void ProcessInput();
    void GameLoop();
    void Draw();
    void Update();
    void UpdateScore();
    void Victory();
    void Lose();

    SDL_Renderer* m_renderer;
    SDL_Texture* m_levelTexture;
    SDL_Texture* m_playerTexture;
    SDL_Texture* m_ballTexture;
    SDL_Texture* m_bricksTexture;
    SDL_Texture* m_upgradesTexture;
    SDL_Texture* m_heartTexture;
    SDL_Texture* m_textTexture;

    TTF_Font* m_font;

    Window m_window;
    InputManager m_inputManager;
    Sprite m_sprite;
    GameState m_gameState;
	SoundEffects m_soundEffects;

    Level m_level;
    Player m_player;
	PlayerStats m_playerStats;
    Ball m_ball;

	Bonus m_bonus;
    std::vector <glm::vec2> m_levelPosition;

    Fps m_fps;
};

