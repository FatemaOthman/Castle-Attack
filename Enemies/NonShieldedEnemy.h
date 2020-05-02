#pragma once
#include"Enemy.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class List;


class Tower;
class NonShieldedEnemy: public Enemy
{ int damageToTower;
public:
	NonShieldedEnemy(color r_c, REGION r_region, int d=MaxDistance);
	virtual bool operator>(Enemy*E);

	virtual void Attack(List &ActiveList, Tower &T, int Ts, bool x);
	virtual void Move(Tower &T);
	
	~NonShieldedEnemy();
};

