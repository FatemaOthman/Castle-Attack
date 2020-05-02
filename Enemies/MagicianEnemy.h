#include"Enemy.h"
#pragma once
class List;
class Tower;
class MagicianEnemy:public Enemy
{
	int DistToAttackTower;
	int DecTowerFire;
public:
	void Attack(List& ActiveList,Tower &T, int Ts,bool x);
	void Move(Tower &T);
	virtual bool operator>(Enemy*E);

	MagicianEnemy(color r_c, REGION r_region, int d = MaxDistance);
	~MagicianEnemy();

};

