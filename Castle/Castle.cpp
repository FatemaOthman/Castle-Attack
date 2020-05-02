#include "Castle.h"

#include "..\GUI\GUI.h"
#include"..\ADT\List.h"

Castle::Castle()
{
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
}
void Castle::SetTowersMax(int  h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetMax(h);
	}
}
void Castle::SetTowersPower(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetPower(h);
	}
}
void Castle::SetTowers(double h, int m, double p)
{
	SetTowersHealth(h);
	 SetTowersMax( m);
	 SetTowersPower( p);

}
void Castle::Fight(List& Active,int Count,int ts)
{
	if (Count == 0)
		return;
  Towers[Active.GetHead()->GetData()->GetRegion()].Attack(Active, Count, ts);
	

}
Tower* Castle::GetArrayOfTowers()
{
	return Towers;
}
void  Castle::SetArrayOfTowers(Tower T, int i)
{
	Towers[i] = T;
}