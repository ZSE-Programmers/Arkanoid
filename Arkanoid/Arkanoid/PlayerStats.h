#pragma once
#include <iostream>

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats(){};

	void ShowStats(); //cmd

	void CounterAdd();

    int GetLife(){ return m_life; };
	void LifeAdd();
	void LifeSubtract();

private:
	int m_counterBonuce;
	int m_life;
};