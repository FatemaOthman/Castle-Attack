#include "MagicianEnemy.h"
#include"..\Castle\Tower.h"
#include"..\ADT\List.h"


void MagicianEnemy::Attack(List& ActiveList,Tower &T, int Ts, bool x)
{

	if (Distance == 60)
	{
		if(x)
		PlaySound("Fairy Dust Magic Sound Effect.wav", NULL, SND_FILENAME | SND_SYNC);
	}
	if (Health == 0)
	{
		if (KTS == -1)
		{
			KTS = Ts;
			KillDelay = Ts - FirstShotTime;
		}
		return;
	}
	if (ActiveList.IsEmpty())
		return;
	if ((Ts == ArrivalTime || Ts> LastShootingTime + ReloadTime))
	{

		LastShootingTime = Ts;

		Node *Temp = ActiveList.GetHead();//->GetData();
		while (Temp != NULL)
		{
			if (Temp->GetData()->GetDistance() == Distance&&Temp->GetData()->GetK() != 3 && Temp->GetData()->GetHealth() != 0)
			{
				Temp->GetData()->WithMagiacian = true;
				Temp->GetData()->SetHealth(((Temp->GetData()->GetHealth()) + ceil((double)FirePower / (k*2.00))));


			}
			Temp = Temp->GetNext();
		}
		if (Distance == DistToAttackTower)
			T.SetPower((T.GetPower()*DecTowerFire));
	}
}

void  MagicianEnemy::Move(Tower &T)
{
	WithMagiacian = false;
	if (Distance - T.GetPavedArea() <= 1)
		return;
	else
		DecrementDist();
}

MagicianEnemy::MagicianEnemy(color r_c, REGION r_region, int d):Enemy(r_c, r_region,d)
{
	DistToAttackTower = 10;
	DecTowerFire = 1 / FirePower;
	k = 3;
}

bool MagicianEnemy::operator>(Enemy*E)
{
	return ((E->GetK() == 2) ? false : (Priority < E->GetPriority()));
}

MagicianEnemy::~MagicianEnemy()
{
}
