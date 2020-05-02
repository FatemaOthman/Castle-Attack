#include "Enemy.h"

#include"..\Castle\Tower.h"
#include"..\ADT\List.h"

Enemy::Enemy(color r_c, REGION r_region, int d)
{
	Clr = r_c;
	Region = r_region;
	WithMagiacian = false;
	SetDistance(d);
	FirstShotTime = -1;
	KTS = -1;
	Discovered = false;
	LastShootingTime = -1;
	KillDelay = 0;
}

Enemy::~Enemy()
{
}
void Enemy::SetDiscovered(bool X)
{
	Discovered = X;
}

color Enemy::GetColor() const
{
	return Clr;
}
void Enemy::TowerAttack(double TFirePower)
{
	Health = TFirePower>Health?0:Health-TFirePower;
	//Health = 0;
}
bool Enemy::operator==(Enemy* E)
{
	return E->ID == ID;
}
int Enemy::GetHealth()
{
	return Health;
}

REGION Enemy::GetRegion() const
{
	return Region;
}

void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}
int Enemy::GetFirePower()
{
	return FirePower;
}
void Enemy::SetFirePower(int x)
{
	FirePower = x;
}
int Enemy::GetReloadTime()
{
	return ReloadTime;
}
void Enemy::SetReloadTime(int x)
{
	ReloadTime = x;
}
int Enemy::GetArrivalTime()
{
	return ArrivalTime;
}
void Enemy::SetArrivalTime(int x)
{
	ArrivalTime = x;
	LastShootingTime = ArrivalTime;
	Priority = ArrivalTime;

}
void Enemy::SetID(int id)
{
	ID = id;
}
void Enemy::SetHealth(double x)
{
	Health = x > 0 ? x : 0;
}
void  Enemy::SetData(int id, double h, int FP, int RT, int AT)
{
	SetFirePower(FP);
	SetHealth(h);
	SetReloadTime(RT);
	SetArrivalTime(AT);
	SetID(id);
}

int Enemy::GetID()
{
	return ID;
}
string Enemy::RegionToString(int x)
{
	if (Region == 0)
		return "A";
	if (Region == 1)
		return "B";
	if (Region == 2)
		return "C";
	if (Region == 3)
		return "D";
}

string Enemy::ColorToString(color c)
{
	if (Clr == DARKBLUE)
		return "DARK BLUE";
	if (Clr == DARKOLIVEGREEN)
		return "DARKOLIVEGREEN";
	if (Clr == ORANGERED)
		return "ORANGERED";
	else
		return " ";
}

void Enemy::SetKTS(int x)
{
	KTS = x;
}
int Enemy::GetKTS()
{
	return KTS;
}
 void Enemy:: CalcPriority(double C1, double C2, double C3, int Ts)
{
	 Priority = ArrivalTime;
}
 double Enemy:: GetPriority()
 {
	 return Priority;
 }
int Enemy::GetKillDelay()
{
	return KillDelay;
}
void Enemy::SetKillDelay(int x)
{
	KillDelay = x;
}
int  Enemy::GetFirstShootingTime()
{
	return FirstShotTime;
}
void  Enemy::SetFirstShootingTime(int x)
{
	FirstShotTime = x;
}
int Enemy::GetK()
{
	return k;
}
void Enemy::SetRegion(REGION R)
{
	Region = R;
}
/* void Enemy::Move(int Ts)
{
}
//All enemies can move
 void Enemy::Attack(List<Enemy*> ActiveList,/*Tower T,int Ts)
 {

}*/