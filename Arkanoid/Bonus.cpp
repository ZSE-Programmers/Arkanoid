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
	std::uniform_int_distribution <int> roll(1, 3);

	switch (roll(randomEngine))
	{
	case 1://upgrade platform
		m_player->ChangePlatformLength(1);
		std::cout << "add platform\n";
		break;
	case 2://add life
		m_playerStats->LifeAdd();
		std::cout << "add life\n";
		break;
	case 3://downgrade platform
		m_player->ChangePlatformLength(-1);
		std::cout << "subtract platform\n";
		break;
	}
}