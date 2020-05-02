#pragma once
#include"Enemy.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class List;

class Tower;
class ShieldedEnemy:public Enemy
{ 
	float priority;
	int DamageToTower;
public:
	ShieldedEnemy( color r_c, REGION r_region, int d = MaxDistance);
	virtual void Move(Tower &T); //new
	virtual bool operator>(Enemy*E);


	virtual void Attack(List &ActiveList, Tower &T, int Ts, bool x); //new
	void CalcPriority(double C1, double C2, double C3, int Ts);
	~ShieldedEnemy();
};

