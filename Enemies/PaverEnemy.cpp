#include"PaverEnemy.h"

#include"..\Castle\Tower.h"
#include"..\ADT\List.h"

PaverEnemy::PaverEnemy(color r_c, REGION r_region, int d) :Enemy(r_c, r_region, d)
{

	
	k = 1;

}

void  PaverEnemy::Move(Tower &T)
{
	WithMagiacian = false;
	if (Distance - T.GetPavedArea() <= 1)
		return;
	else
		DecrementDist();
}

void PaverEnemy::Attack(List &ActiveList, Tower &t, int TS, bool x)
{

	if (Health == 0)
	{
		if (KTS == -1)
			KTS = TS;
		KillDelay = TS - FirstShotTime;

		return;
	}
	if ((TS == ArrivalTime || TS>LastShootingTime + ReloadTime))
	{
		if (Distance <= 2)
			return;
		Distance -= FirePower;

		if (Distance - FirePower < t.GetPavedArea())
		{
			if (x)
				PlaySound("Shovel Digging Dirt [SOUND EFFECT].wav", NULL, SND_FILENAME | SND_SYNC);
		}
		if (Distance <= 30)
		{
			if(Distance<t.GetPavedArea())
			t.SetPavedArea(Distance);
		}
		LastShootingTime = TS;
	}


}
bool PaverEnemy::operator>(Enemy*E)
{
	return ((E->GetK() == 2) ? false : (Priority < E->GetPriority()));
}
PaverEnemy::~PaverEnemy()
{

}
