#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	m_counterBonuce = 0;
	m_life = 3;
}

void PlayerStats::ShowStats()
{
	std::cout << "-----------------------" << std::endl
		<< "Life:                 " << m_life << std::endl
		<< "Counter:              " << m_counterBonuce << std::endl
		<< "-----------------------"<< std::endl;
}




void PlayerStats::CounterAdd()
{
	m_counterBonuce++;
}

void PlayerStats::LifeAdd()
{
	m_life++;
}

bool PlayerStats::LifeSubtract()
{
	if (--m_life)
	{
		return 1; 
	}
	else
	{
		return 0; //to -> game over
	}
}