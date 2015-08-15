#pragma once

#include "Player.h"
#include "PlayerStats.h"

#include <ctime>
#include <random>
#include <iostream>
class Bonus
{
public:
	Bonus();
	~Bonus();
	void Init(Player* player, PlayerStats* playerstats);
	void ActivateBonus();

private:

	Player* m_player;
	PlayerStats* m_playerStats;
};