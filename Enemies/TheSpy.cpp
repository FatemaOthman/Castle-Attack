#include "TheSpy.h"
#include"..\Castle\Tower.h"
#include"..\ADT\List.h"

TheSpy::TheSpy(color r_c, REGION r_region, int d) : Enemy(r_c, r_region, d)
{
	k = 0;
	killCount = 0;
	Discovered = false;
	}

void TheSpy::Move(Tower &T)
{
	if (Distance - T.GetPavedArea() <= 1)
		return;
	else
		DecrementDist();
}
void TheSpy::Attack(List &l, Tower &T, int t, bool x)
{
	Node*ptr = l.GetHead();
	Enemy*E;
	if (Health == 0)
	{
		KTS = t;
		KillDelay = t - FirstShotTime;
		T.SetSpy(false);
		return;
	}
	if (Discovered)
	{
		if (x)
		PlaySound("explor.wav", NULL, SND_FILENAME | SND_SYNC);

		if (KTS == -1)
		{
			KTS = t;
			KillDelay = t - FirstShotTime;
		}
		int d = 0;
		double damage;
		while (ptr)
		{
			E = ptr->GetData();
			if (E->GetDistance() <= Distance + 4 && E->GetDistance() >= Distance - 4)
			{
				d = abs(Distance - E->GetDistance()) + 1;
				damage = FirePower / d;
				E->TowerAttack(damage);
			}

			ptr = ptr->GetNext();
		}
		if (Distance < 7)
			T.EnemyAttack(FirePower / Distance);
		Health = 0;

		return;
	}
	if ((t == ArrivalTime || t > LastShootingTime + ReloadTime))
	{

		LastShootingTime = t;

		while (ptr)
		{
			E = ptr->GetData();
			if (E->GetDistance() == Distance && ID != E->GetID())
			{
				if (x)
				PlaySound("Kill.wav", NULL, SND_FILENAME | SND_SYNC);
				E->SetHealth(0);
				E->SetKTS(t);
				if (E->GetFirstShootingTime()==-1)
				  E->SetKillDelay(0);
				else
				{
					int x = t - GetFirstShootingTime();
					E->SetKillDelay(x);
				}
				killCount++;
				break;
			}
			ptr = ptr->GetNext();
		}
	}
	if (killCount >= 3)
	{
		Discovered = true;
		T.SetSpy(true);
	}
}
bool TheSpy::operator>(Enemy*E)
{
	return ((E->GetK() == 2) ? false : (Priority < E->GetPriority()));
}
TheSpy::~TheSpy()
{
}
