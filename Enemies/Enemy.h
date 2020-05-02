#pragma once
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
//#include"..\ADT\List.h"
//#include"..\ADT\List.cpp"
//#include"..\Castle\Tower.h"
// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class List;
class Tower;
class Enemy
{

protected:

	
	int ID;         //Each enemy has a unique ID (sequence number)
	color Clr;	    //Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;  //Region of this enemy
	int Distance;	//Horizontal distance between enemy & the tower of its region                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health
	int FirePower;
	int ReloadTime;
	int ArrivalTime;
	int FirstShotTime ;
	int LastShootingTime;
	int KTS;
	int KillDelay;
	int k;
	bool Discovered;
	double Priority;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy(color r_c, REGION r_region, int d = MaxDistance);
	virtual ~Enemy();

	color GetColor() const;
	REGION GetRegion() const;

	void DecrementDist();

	void SetDiscovered(bool);
	void SetDistance(int d);
	int GetDistance() const;

	int GetFirePower();
	void SetFirePower(int x);

	int GetReloadTime();
	void SetReloadTime(int x);
	int GetK();
	int GetArrivalTime();
	void SetArrivalTime(int x);
	int GetHealth();
	void SetID(int id);
	void SetHealth(double x);
	void SetData(int id, double h, int FP, int RT, int AT);
	int GetID();
	void SetRegion(REGION R);
	void SetKTS(int);
	int GetKTS();

	int GetKillDelay();
	void SetKillDelay(int);

	int GetFirstShootingTime();
	void SetFirstShootingTime(int);

	void TowerAttack(double TFirePower);
	bool operator==(Enemy* E);
	virtual bool operator>(Enemy*E) = 0;

	bool WithMagiacian;

	string RegionToString(int r);
	string ColorToString(color c);
	virtual void CalcPriority(double C1, double C2, double C3, int Ts);
	int NextShootingTime;
	double GetPriority();
	// Virtual Functions: ----------------

	virtual void Move(Tower &T) =0;	    //All enemies can move
	virtual void Attack(List &ActiveList,Tower &T,int Ts,bool x)=0;	//All enemies can attack (attacking is paving or shooting)

	//
	// TODO: Add More Member Functions As Needed
	//

};


