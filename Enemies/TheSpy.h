#pragma once
#include"Enemy.h"
class List;

class Tower;
class TheSpy : public Enemy
{
	int killCount;
public:
	TheSpy(color r_c, REGION r_region, int d=60);
	virtual bool operator>(Enemy*E);

	virtual void Move(Tower &t) ;//All enemies can move
	virtual void Attack(List &l,Tower &T,int t, bool x) ;	//All enemies can attack (attacking is paving or shooting)

	~TheSpy();
};

