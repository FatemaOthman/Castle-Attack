#include "Tower.h"
#include"..\ADT\List.h"
#include<time.h>
Tower::Tower()
{
	Spy = false;
	TotalDamage = 0;
	PavedArea = 30;

}
void Tower::SetHealth(double h)
{
	if (h > 0)
	{
		Health = h;
		IntialHealth = h;
	}
	else
		Health = 0; // killed
}

double Tower::GetHealth() const
{
	return Health;
}
void  Tower::SetMax(int m)
{
	Max = m;
}
int  Tower::GetMax()
{
	return Max;
}
void  Tower::SetPower(double p)
{
	Power = p;
}
double  Tower::GetPower()
{
	return Power;
}
void Tower::Attack(List&Active, int EnemyCount,int Ts)
{
	double damage;
	Enemy*E;
	Node*ptr = Active.GetHead();
	for (int i = 0; i < EnemyCount; i++)
	{
		if (i > Max)
			break;
		E = ptr->GetData();
		if (E->GetK() != 0)
		{
			damage =(double) Power /(double) (E->GetK()*E->GetDistance());
			if (E->WithMagiacian)
				damage *= 0.5;
			E->TowerAttack(damage);
			if (E->GetHealth() == 0)
			{
				E->SetKTS(Ts);
				int x = E->GetKTS() - E->GetFirstShootingTime();
				E->SetKillDelay(x);

			}

			if (E->GetFirstShootingTime() == -1)
			{
				E->SetFirstShootingTime(Ts);
			}
		}
		ptr = ptr->GetNext();
	}

}
int Tower::GetPavedArea()
{
	return PavedArea;
}
void Tower::SetPavedArea(int x)
{
	PavedArea = x;
}
double Tower::GetTotalDamage()
{
	return  TotalDamage;
}
void Tower::SetTotalDamage(double x)
{
	if (Health  == 0)
	{
		TotalDamage = IntialHealth;
	}
	else
	TotalDamage += x;
}
bool Tower::GetSpy()
{
	return Spy;
}
void Tower::SetSpy(bool s)
{
	Spy = s;
}
void Tower::EnemyAttack(double TFirePower)
{
	Health = TFirePower>Health ? 0 : Health - TFirePower;
}
