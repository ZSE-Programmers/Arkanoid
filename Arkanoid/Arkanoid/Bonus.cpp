#include "Bonus.h"

Bonus::Bonus() : m_player(nullptr), m_playerStats(nullptr)
{
}

Bonus::~Bonus()
{
}

void Bonus::Init(Player* player, PlayerStats* playerstats)
{
	m_player = player;
	m_playerStats = playerstats;
}


void Bonus::ActivateBonus()
{
	static std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution <int> roll(1, 2);

	switch (roll(randomEngine))
	{
	case 1://upgrade platform
		m_player->ChangePlatformLength(1);
		break;
	case 2://add life
		m_playerStats->LifeAdd();
		break;
	}
}