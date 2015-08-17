#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	m_counterBonuce = 0;
	m_life = 3;
}

void PlayerStats::ShowStats()
{
}

void PlayerStats::CounterAdd()
{
	m_counterBonuce++;
}

void PlayerStats::LifeAdd()
{
	m_life++;
}

void PlayerStats::LifeSubtract()
{
    m_life--;
}