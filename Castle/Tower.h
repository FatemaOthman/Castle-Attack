#pragma once

/*#include"..\ADT\List.h"
#include"..\ADT\List.cpp"*/
//#include"..\ADT\Queue.h"
//#include"..\ADT\Queue.cpp"
#include"..\Enemies\Enemy.h"
class List;
class Tower
{
	double Health;
	int Max;
	double Power;
	int PavedArea;
	double TotalDamage;
	bool Spy;
	double IntialHealth;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Tower();
	void SetHealth(double h); 
	double GetHealth() const;
	void SetMax(int m);
	int GetMax();
	void SetPower(double p);
	double GetPower();
	void Attack(List&Active, int EnemyCount,int Ts);
	int GetPavedArea();
	void SetPavedArea(int);
	double GetTotalDamage();
	void SetTotalDamage(double);
	void EnemyAttack(double);
	bool GetSpy();
	void SetSpy(bool);


	//
	// TODO: Add More Member Functions As Needed
	//

};

