#include "ShieldedEnemy.h"
#include"..\Castle\Tower.h"
#include"..\ADT\List.h"

ShieldedEnemy::ShieldedEnemy(color r_c, REGION r_region,int d) : Enemy( r_c, r_region, d)
{
	
	k = 2;
}

void ShieldedEnemy::CalcPriority(double C1, double C2, double C3,int Ts)
{
	int RemTimeToShoot;
	if (Ts - LastShootingTime == ReloadTime + 1 || LastShootingTime == ArrivalTime)
		RemTimeToShoot = 0;
	else
		RemTimeToShoot = LastShootingTime + ReloadTime + 1 - Ts;
	Priority = ((double)(FirePower) / (double)(Distance))*C1 + ((double)C2 / ((double)(1 + RemTimeToShoot))) + Health*C3;
}

void ShieldedEnemy::Attack(List &ActiveList, Tower &T, int Ts, bool x)
{
	if (Health == 0)
	{

		if (KTS == -1)
		{
			KTS = Ts;
			KillDelay = Ts - FirstShotTime;
		}
		return;
	}
	double DamageToTower;

	if ((Ts == ArrivalTime || Ts>LastShootingTime + ReloadTime))
	{

			LastShootingTime = Ts;

		if (T.GetSpy())
		{
			Node*ptr= ActiveList.GetHead();
			while (ptr)
			{
				if (ptr->GetData()->GetK() == 0)
				{
					int d = abs(ptr->GetData()->GetDistance() - Distance);
					DamageToTower = (double)((k *1.00) / (d*1.00))*FirePower;
					ptr->GetData()->TowerAttack(DamageToTower);
					ptr->GetData()->SetDiscovered(true);
					ptr->GetData()->SetFirstShootingTime(Ts);
					if (ptr->GetData()->GetHealth() == 0)
					{
						ptr->GetData()->SetKTS(Ts);
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
bool ShieldedEnemy::operator>(Enemy*E)
{
	return((E->GetK() == 2) ? (Priority > E->GetPriority()) : true);

}
void ShieldedEnemy::Move(Tower &T)
{
	WithMagiacian = false;
	
	if(Distance - T.GetPavedArea() <= 1)
		return;
	else
		DecrementDist();


}

ShieldedEnemy::~ShieldedEnemy()
{
}
