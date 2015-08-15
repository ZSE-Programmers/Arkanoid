#pragma once
#include <iostream>

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats(){};

	void ShowStats(); //cmd

	void CounterAdd();

	void LifeAdd();
	bool LifeSubtract();

private:
	int m_counterBonuce;
	int m_life;
};