#pragma once
#include"Enemy.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
class List;


class Tower;
class PaverEnemy :public Enemy
{ 
public:
	PaverEnemy( color r_c, REGION r_region, int d = MaxDistance);
	virtual bool operator>(Enemy*E);

	void Move(Tower &t);
	void Attack(List&ActiveList, Tower &T, int Ts, bool x);
	~PaverEnemy();
};