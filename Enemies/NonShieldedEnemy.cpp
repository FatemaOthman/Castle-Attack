#include "NonShieldedEnemy.h"
#include"..\Castle\Tower.h"
#include"..\ADT\List.h"


NonShieldedEnemy::NonShieldedEnemy(color r_c, REGION r_region, int d) :Enemy(r_c, r_region, d)
{
	k = 1;
}


NonShieldedEnemy::~NonShieldedEnemy()
{
}
void NonShieldedEnemy::Move(Tower &T)
{ 
	WithMagiacian = false;
	
	if (Distance - T.GetPavedArea() <= 1)
		return;
	else
		DecrementDist();

}
void NonShieldedEnemy::Attack(List& ActiveList, Tower &T, int t, bool x)
{
	if (Health == 0)
	{
		if (KTS == -1)
		{
			KTS = t;
			KillDelay = t - FirstShotTime;
		}
		return;
	}
	double DamageToTower;

	if ((t == ArrivalTime || t>LastShootingTime + ReloadTime))
	{

		LastShootingTime = t;
		if (T.GetSpy())
		{
			Node*ptr = ActiveList.GetHead();
			while (ptr)
			{
				if (ptr->GetData()->GetK() == 0)
				{
					int d = abs(ptr->GetData()->GetDistance() - Distance);
					DamageToTower = (double)((k *1.00) / (d*1.00))*FirePower;
					ptr->GetData()->TowerAttack(DamageToTower);
					ptr->GetData()->SetDiscovered(true);
					ptr->GetData()->SetFirstShootingTime(t);
					if (ptr->GetData()->GetHealth() == 0)
					{
						ptr->GetData()->SetKTS(t);
					}
					return;
				}
				ptr = ptr->GetNext();
			}
		}
		DamageToTower = (double)((k *1.00) / (Distance*1.00))*FirePower;
		T.EnemyAttack(DamageToTower);
		T.SetTotalDamage(DamageToTower);
	}
}
bool NonShieldedEnemy::operator>(Enemy*E)
{
	return ((E->GetK() == 2) ? false : (Priority < E->GetPriority()));
}



